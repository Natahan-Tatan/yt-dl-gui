# yt-dl-gui

**WORK IN PROGRESS**

Front-end for [youtube-dl](https://youtube-dl.org/) tool. **For the moment only for Linux**.

It requires the wget command (for download lastest youtube-dl program), python to execute the tool and ffmpeg for convert to audio.

First time you start, you must trigger the youtube-dl download in **File** menu.

## Compilation
### Requirement

This program required fltk libraries and pthread.

### Make

To copile this program, go to the root folder an do:
```
make CONF=Release
```
The resulting executable is in **dist/Release**.
