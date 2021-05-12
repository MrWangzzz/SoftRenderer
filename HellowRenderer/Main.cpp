#include"tgaimage.h"
const TGAColor red = TGAColor(255,0,0,255);

void Line(int x1, int y1, int x2, int y2, TGAImage &image, TGAColor color);
int main(int argc,char** argv) 
{
	TGAImage image(100, 100, TGAImage::RGB);
//	image.set(52, 41, red);
	image.flip_vertically();
	Line(0, 0, 40, 40, image, red);
	image.write_tga_file("lesson00.tga");
	return 0;
}
void Line(int x1,int y1,int x2,int y2,TGAImage &image,TGAColor color)
{
	int dx = x2 - x1;
	int dy = y2 - y1;
	float dl = 0.01f;
	for(float i = 0.0; i < 1.0; i+= dl)
	{
		int x = x1 + dx * i;
		int y = y1 + dy * i;
		image.set(x, y, color);
	}
}