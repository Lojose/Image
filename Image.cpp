#include <iostream>
#include "Image.h"
#include "Image.h"
#include "Global.h"
#include "Frame.h"

extern Frame frame;
Image::Image(int h, int w, const char *filename): h(h), w(w) {}

void Image::startingPt(int x, int y) {
	this->x = x; 
	this->y = y; 
}

void Image::draw_rect(int x, int y, int w, int h, byte r, byte g, byte b) {
	if (frame.isOutside(&x, &y)) return;
	int x0 = x;
	int x1 = x + w;
	int y0 = y;
	int y1 = y + h;
	frame.clamp(&x0, &y0);
	frame.clamp(&x1, &y1);
	for (int y = y0; y < y1; ++y) {
		for (int x = x0; x < x1; ++x) {
			frame.setPixel(x, y, r, g, b);
		}
	}
}

void Image::draw_frame(double t){ 
	const double pps = 80; // pixels per second 
	draw_rect(x + t*pps, y + t*pps, w, h, r, g, b);
}