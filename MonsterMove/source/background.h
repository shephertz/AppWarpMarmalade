
#ifndef __BACKGROUND__
#define __BACKGROUND__

#include "game.h"

class Background
{
	float width,height;
	CIw2DImage *bg;
	float imgWidth,imgHeight;
	bool effect;
	float ex,ey;
public:
	Background();
	~Background();
	void Init(std::string path,float w, float h,bool effect_on_off = false);
	void Render();
};

#endif