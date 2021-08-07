/*
 * Copyright (C) 2021 Natahan Tatan
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* 
 * \file VideoDL.cpp
 * \author Natahan Tatan
 * 
 * \version 1.0
 * \date July 13, 2020, 5:07 PM
 */

#include <sys/stat.h>
#include <FL/Fl.H>
#include <algorithm>

#include "VideoDL.hpp"

VideoDL::VideoDL(std::string const& outdir, std::string const& url, bool audioOnly, std::string const& audioType): _outdir(outdir), _url(url), _audioOnly(audioOnly), _audioType(audioType), _mutex(PTHREAD_MUTEX_INITIALIZER), _stop(false), _progress(0)
{
   pthread_create(&_thread, nullptr, Process, this);
}

VideoDL::VideoDL(const VideoDL& orig):VideoDL(orig._outdir, orig._url, orig._audioOnly, orig._audioType) {}

VideoDL::~VideoDL() 
{
    pthread_join(_thread, nullptr);
}

std::string VideoDL::GetPathToYoutubeDl()
{
    struct stat i;
    
    std::string configPath = getenv("HOME");
    configPath += "/.config";

    if(stat(configPath.c_str(), &i) != 0)
    {
        mkdir(configPath.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    }
    
    configPath += "/yt-dl-gui";
    
    if(stat(configPath.c_str(), &i) != 0)
    {
        mkdir(configPath.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    }
    
    return configPath + "/youtube-dl";
}

bool VideoDL::DownloadLastYoutubeDl()
{
    std::string exe = GetPathToYoutubeDl();
    
    std::string dlCmd = "wget https://yt-dl.org/downloads/latest/youtube-dl --output-document ";
    dlCmd += exe;
    
    std::array<char, 1024> buffer;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(dlCmd.c_str(), "r"), pclose);
    
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) 
    {
        std::cout << buffer.data();   
    }
    
    struct stat i;
    
    if(stat(exe.c_str(), &i) != 0)
    {
        fl_alert("Error when attempts to get last youtube-dl version....");
        return false;
    }
    else
    {
        fl_message("Lastest youtube-dl sucessfuly downloaded");
    }
    
    chmod(exe.c_str(), S_IRWXU | S_IRWXG | S_IROTH);
    
    return true;
}

float VideoDL::GetProgress()
{
    pthread_mutex_lock(&_mutex);
    float progress = _progress;
    pthread_mutex_unlock(&_mutex);
    
    return progress;
}

void* VideoDL::Process(void* p)
{
    VideoDL* data = static_cast<VideoDL*>(p);
    
    std::string exe = GetPathToYoutubeDl();
    
    struct stat i;
    
    if(stat(exe.c_str(), &i) != 0)
    {
        Fl::lock();
        fl_alert("The youtube-dl program must be download.");
        if(!DownloadLastYoutubeDl())
        {
            return nullptr;
        }
        Fl::unlock();
    }
    
    std::string cmd = exe + " " + data->_url  + "--no-color --newline --output \"" + data->_outdir + "/%(title)s.%(ext)s\" ";
    
    if(data->_audioOnly)
    {
        cmd += " -x --audio-format=\"" + data->_audioType + "\"";
    }
    else
    {
        cmd += " -f best";
    }
    
    std::array<char, 1024> buffer;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
    
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) 
    {
        std::cout << buffer.data();  
        
        std::string str = buffer.data();
        int firstSpace = str.find(" ");
        int firstPercent = str.find("%");
        
        if(firstSpace != std::string::npos && firstPercent != std::string::npos)
        {
            std::string value = str.substr(firstSpace, firstPercent-firstSpace);
        
            if(!value.empty())
            {
                pthread_mutex_lock(&data->_mutex);
                data->_progress = std::stof(value);
                pthread_mutex_unlock(&data->_mutex);
            }
        }
        else
        {
            if(str.find("ERROR") != std::string::npos || str.find("error") != std::string::npos)
            {
                fl_alert("Error: %s", str.c_str());
                std::cout << "Failure of process" << std::endl;
                return nullptr;
            }
        }
        
    }
    
    pthread_mutex_lock(&data->_mutex);
    data->_progress = 101;
    pthread_mutex_unlock(&data->_mutex);
    
    std::cout << "End of process" << std::endl;
    return nullptr;
}

