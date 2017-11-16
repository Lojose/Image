#pragma once
#include <vector>
#include "Global.h"
class Image {
public:
	Image(int h, int w, const char *filename); 
	void draw_rect(int x, int y, int w, int h, byte r, byte g, byte b); 
	void draw_frame(double t); 
	void startingPt(int x, int y); 
	int x;
	int y;
private:
	byte r; 
	byte g; 
	byte b;  
	int h;
	int w;  
};