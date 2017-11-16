#include <iostream>
#include <sstream>
#include <sys/stat.h>
#include <stdio.h>
#include <cassert>
#include <cstring>
#include "Global.h"
#include "Frame.h"
#include "Image.h"

Frame frame;

int main(int argc, char * argv[]) {
	byte *p; 
	p = new byte[W * H * 3];

	const char *cmd1 =
		"ffmpeg\\bin\\ffmpeg.exe "
		"-i apple_raw.png "
		"-f rawvideo "
		"-pix_fmt yuv420p -"; 
	const char * cmd2 =
		"ffmpeg\\bin\\ffmpeg.exe "
		"-y                  "
		"-hide_banner        "
		"-f rawvideo         " // input to be raw video data
		"-pixel_format rgb24 "
		"-video_size 720x480 "
		"-r 60               " // frames per second
		"-i -                " // read data from the standard input stream
		"-pix_fmt yuv420p    " // to render with Quicktime
		"-vcodec mpeg4       "
		"-an                 " // no audio
		"-q:v 5              " // quality level; 1 <= q <= 32
		"output.mp4          ";

#ifdef _WIN32

	FILE * pipein =  _popen(cmd1, "rb");
	//FILE * pipein =  _popen("100MB.bin", "rb");
	FILE * pipeout = _popen(cmd2, "wb");
#else
	FILE * pipein = popen(cmd1, "rb");
	File * pipout = popen (cmd2, "wb")

#endif
	if (pipeout == 0) {
		std::cout << "error: " << strerror(errno) << std::endl;
		return 1;
	}
	

	//Image img( ??);  
	//img.startingPt(0, 0); 
	int num_frames = duration_in_seconds * frames_per_second;
	for (int i = 0; i < num_frames; ++i) {
		double time_in_seconds = i / frames_per_second; 
		//img.draw_frame(time_in_seconds); 
		//frame.write(pipeout);
		//frame.clear(); 
	}

	fflush(pipeout);
	fflush(pipein); 
#ifdef _WIN32
	_pclose(pipeout);
	_pclose(pipein); 

#else
	pclose(pipeout);
	pclose(pipein)
#endif
	std::cout << "num_frames: " << num_frames << std::endl;
	std::cout << "Done." << std::endl;
	return 0;
}