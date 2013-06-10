
#include "background.h"

Background::Background()
{
	ex = 0;
	ey = 0;

	bg = NULL;
}

Background::~Background()
{
	if(bg != NULL)
		delete bg;
}
void Background::Init(std::string path,float w, float h,bool effect_on_off)
{
	bg = Iw2DCreateImage(path.c_str());
	width = w;
	height = h;
	imgHeight = bg->GetHeight();
	imgWidth = bg->GetWidth();

	effect = effect_on_off;
}
void Background::Render()
{
	for(float i=0; i<width+(-1*ex); i+=imgWidth)
	{
		for(float j=0; j<height+(-1*ey); j+=imgHeight)
		{
			Iw2DDrawImage(bg,CIwSVec2(i+ex,j+ey));
		}
	}

	if(effect == true)
	{
		ex -= 0.5;
		ey -= 0.5;

		if(ex < (-1)*bg->GetWidth())
			ex = 0;
		if(ey < (-1)*bg->GetHeight())
			ey = 0;
	}
}