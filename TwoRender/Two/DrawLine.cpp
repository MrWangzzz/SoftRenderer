#include <iostream>
#include <vector>
#include<SDL.h>
#include "Random.h"
#include "Vector.h"
#include "FPS.h"
using namespace std;

void line(int x0, int y0, int x1, int y1, SDL_Renderer* pRenderer)
{
	bool steep = false;
	if (std::abs(x0 - x1) < std::abs(y0 - y1))
	{
		std::swap(x0, y0);
		std::swap(x1, y1);
		steep = true;
	}
	if (x0 > x1) { // make it left−to−right 
		std::swap(x0, x1);
		std::swap(y0, y1);
	}
	int dx = x1 - x0;
	int dy = y1 - y0;
	float derror = std::abs(dy / float(dx));
	float error = 0;
	int y = y0;
	for (int x = x0; x <= x1; x++)
	{
		if (steep)
		{
			SDL_RenderDrawPoint(pRenderer, y, x);
		}
		else
		{
			SDL_RenderDrawPoint(pRenderer, x, y);
		}
		error += derror;
		if (error > .5)
		{
			y += (y1 > y0 ? 1 : -1);
			error -= 1.;
		}
	}
}


void DrawFlatBottom(Vector2& t1, Vector2& t2, Vector2& t3, SDL_Renderer* pRenderer)
{
	float slope1 = (t2.x - t1.x) / (t2.y - t1.y);
	float slope2 = (t3.x - t1.x) / (t3.y - t1.y);
	float curx1 = t1.x;
	float curx2 = t1.x;
	for (int i = t1.y; i <= t2.y; i++)
	{
		line(curx1, i, curx2, i, pRenderer);
		curx1 += slope1;
		curx2 += slope2;
	}
}

void DrawFlaTop(Vector2& t1, Vector2& t2, Vector2& t3, SDL_Renderer* pRenderer)
{
	float slope1 = (t2.x - t1.x) / (t2.y - t1.y);
	float	slope2 = (t2.x - t3.x) / (t2.y - t3.y);
	float curx1 = t2.x;
	float curx2 = t2.x;
	//cout << t1.x<<"t1y"<<t1.y<<endl;
	//cout << t2.x << "t2y" << t2.y << endl;
	//cout << t3.x << "t3y" << t3.y << endl;
	for (int i = t2.y; i >= t1.y; i--)
	{
		line(curx1, i, curx2, i, pRenderer);
		curx1 -= slope1;
		curx2 -= slope2;
	}
}

void Old11DrawTriangle(Vector2& t1, Vector2& t2, Vector2& t3, SDL_Renderer* pRenderer)
{


	if (t2.y == t3.y)
	{
		DrawFlatBottom(t1, t2, t3, pRenderer);
	}
	else if (t1.y == t3.y)
	{
		DrawFlaTop(t1, t2, t3, pRenderer);
	}
	else
	{

		float t4x = (t3.y - t1.y) / (t2.y - t1.y) * (t2.x - t1.x) + t1.x;
		Vector2 t4(t4x, t3.y);
		DrawFlatBottom(t1, t4, t3, pRenderer);
		DrawFlaTop(t4, t2, t3, pRenderer);
	}
}



int main(int argc, char* argv[])
{
	//ifstream inf;
	//char buffer[256];
	//inf.open("D:\\MeilinRenderer\\TwoRender\\Two\\Obj\\african_head.obj", ios::in);
	//
	//TGAImage image(500, 500, TGAImage::RGB);
	////line(0, 0, 100, 100, image, white);
	//image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	//image.write_tga_file("output.tga");


	SDL_Window* window = NULL;
	window = SDL_CreateWindow("MerLinTwoRender", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	if (!window)
	{
		printf("Can't create window");
		return 1;
	}

	SDL_Event windowEvent;

	////平底
	Vector2 t1(30, 20);

	//Vector2 t2(50, 60);

	//Vector2 t3(40, 40);

	Vector2 t2(50, 40);

	Vector2 t3(20, 30);
	while (true) {
		SDL_WaitEvent(&windowEvent);
		if (windowEvent.type == SDL_QUIT)
		{
			break;
		}

		SDL_Renderer* pRenderer = NULL;
		// 创建渲染器
		pRenderer = SDL_CreateRenderer(window, -1, 0);
		// 指定渲染颜色
		SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
		//画线算法
		//line(0, 0, 100, 100, pRenderer);
		// 执行渲染操作，更新窗口

		//for (int i = 0; i < 100; i++)
		//{
		//	SDL_SetRenderDrawColor(pRenderer, Random::Range(0, 255), Random::Range(0, 255), Random::Range(0, 255), SDL_ALPHA_OPAQUE);
		//	int x, y, ex, ey;
		//	x = Random::Range(0, 1000);
		//	y = Random::Range(0, 1000);
		//	ex = Random::Range(0, 1000);
		//	ey = Random::Range(0, 1000);
		//	line(x, y, ex, ey, pRenderer);
		//}


		Old11DrawTriangle(t1, t2, t3, pRenderer);

		SDL_RenderPresent(pRenderer);



	}
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}