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
 * \file VideoDL.h
 * \author Natahan Tatan
 *
 * \version 1.0
 * \date July 13, 2020, 5:07 PM
 */

#ifndef VIDEODL_H
#define VIDEODL_H

#define VERSION "1.0"

#include <string>

#include <cstdio>
#include <iostream>
#include <memory>
#include <unistd.h>

#include <FL/fl_ask.H>

/**
 * \class VideoDL VideoDL.h
 * \brief Download system class
 * This class use youtube-dl program to download, process and save youtube video from URL
 */
class VideoDL 
{
    public:
        /**
         * \brief Constructor
         * @param outdir The directory where the video/audio will be save. This directory will be used like temporary dir for the download too.
         * @param url The url of the youtube video which will be downloaded.
         * @param audioOnly If TRUE, only the audio will be save
         * @param audioType The format of the audio. Only use when "audioOnly" is TRUE. If the format is not available into the video, it will use ffmpeg to convert it.
         */
        VideoDL(std::string const& outdir, std::string const& url, bool audioOnly, std::string const& audioType = "vorbis");
        
        /**
         * \brief Copy contructor. Only implement for security purpose (avoid multiple freeing pointer)
         * @param orig The object to copy.
         */
        VideoDL(const VideoDL& orig);
        
        /**
         * \brief Destructor
         * It will be wait for the end of the download thread.
         */
        virtual ~VideoDL();
        
        /**
         * \brief Get the current percent of progress.
         * @return The current progress in percent.
         */
        float GetProgress();
        
        /**
         * \brief Main function for download thread.
         * @param p The user parameter. In this case it's this class instance itself.
         * @return Nothing.
         */
        static void* Process(void* p);
        
        /**
         * \brief Function to download last release of youtube-dl.
         * Download lastest version and put it into config dir.
         * @return TRUE if the download ended successfully
         */
        static bool DownloadLastYoutubeDl();
        
        /**
         * \brief Get the path to the youtube-dl executable (default in the config dir of the user)
         * For Unix, it is in ~/.config/yt-dl-gui. It uses the "HOME" environment variable.
         * @return The absolute path
         */
        static std::string GetPathToYoutubeDl();
        
    private:
        std::string _outdir;
        std::string _url;
        bool _audioOnly;
        std::string _audioType;
        
        pthread_t _thread;
        pthread_mutex_t _mutex;
        bool _stop;
        
        float _progress;
};

#endif /* VIDEODL_H */

