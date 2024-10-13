#pragma once
#include <graphics.h>

#pragma comment(lib,"WINMM.lib")
#pragma comment(lib,"MSIMG32.lib")

inline void  putimage_alpha(int dst_x, int dst_y, IMAGE* img) {
	int w = img->getwidth();
	int h= img->getheight();
	AlphaBlend(GetImageHDC(GetWorkingImage()), dst_x, dst_y, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}

struct Rect {
	int x, y;
	int w, h;
};

inline void  putimage_ex(IMAGE* img,const Rect* rect_dst,const Rect* rect_src=nullptr){

	static BLENDFUNCTION blend_func = { AC_SRC_OVER,0,255,AC_SRC_ALPHA };
	AlphaBlend(GetImageHDC(GetWorkingImage()), rect_dst->x, rect_dst->y, rect_dst->w, rect_dst->h,
		GetImageHDC(img), rect_src?rect_src->x:0, rect_src ? rect_src->y : 0, 
		rect_src ? rect_src->w : img->getwidth(), rect_src ? rect_src->h : img->getheight(), blend_func);
}

inline void load_audio(LPCTSTR id, LPCTSTR path) {
	static TCHAR str_cmd[512];
	_stprintf_s(str_cmd, _T("open %s alias %s"), path, id);
	mciSendString(str_cmd, NULL, 0, NULL);
}

inline void play_audio(LPCTSTR id, bool is_loop=false) {
	static TCHAR str_cmd[512];
	_stprintf_s(str_cmd, _T("play %s %s from 0"), id, is_loop ? _T("repeat") : _T(""));
	mciSendString(str_cmd, NULL, 0, NULL);
}

inline void stop_audio(LPCTSTR id) {
	static TCHAR str_cmd[512];
	_stprintf_s(str_cmd, _T("stop %s"),id);
	mciSendString(str_cmd, NULL, 0, NULL);
}

inline int range_random(int min, int max) {
	return min + rand() % (max - min + 1);
}

//≤Â÷µº∆À„
inline float lerp(float start, float end, float t) {
	return (1 - t) * start + t * end;
}