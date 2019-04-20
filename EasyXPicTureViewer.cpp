#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<graphics.h> 

enum CMD { CMD_UP = 1, CMD_DOWN = 2,CMD_LEFT=4,CMD_RIGHT=8,CMD_ESC=16};
POINT ptMouse;
int GetCmd()
{
	int c = 0;
	if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W') || GetAsyncKeyState(VK_NUMPAD8))
		c |= CMD_UP;
	if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S') || GetAsyncKeyState(VK_NUMPAD5))
		c |= CMD_DOWN;
	if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D') || GetAsyncKeyState(VK_NUMPAD6))
		c |= CMD_LEFT;
	if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A') || GetAsyncKeyState(VK_NUMPAD4))
		c |= CMD_RIGHT;
	if (GetAsyncKeyState(VK_ESCAPE))
		c |= CMD_ESC;

	MOUSEMSG msg;
	while (MouseHit())
	{
		msg = GetMouseMsg();
		ptMouse.x = msg.x;
		ptMouse.y = msg.y;
	}

	return c;
}

int main(int argc,char * argv[])
{
	int lines=720, cols=480;
	initgraph(lines, cols);
	settextcolor(RGB(120,150,220));
	outtextxy(0, 0, L"This is a picture viewer,support format: jpg / bmp / gif / emf / wmf / ico.");
	outtextxy(0, 20,  L"Move:UP/8/W DOWN/5/S Left/4/A Right/6/D.");
	outtextxy(0, 40, L"PageUp/X: Amplification  PageDown/Z: Shrink.");
	outtextxy(0, 60,  L"Control: Window to Picture Size.");
	outtextxy(0, 80, L"Alt:Window to default size.");
	outtextxy(0, 100, L"Esc: Close windows. R:reset display");
	outtextxy(330, 236, L"EasyX");
	outtextxy(310, 420, L"Dev : Ice2Faith");
	setcolor(RGB(0, 255, 0));
	circle(360, 240, 120);
	setcolor(RGB(255, 0, 0));
	ellipse(200,180,520,300);
	ellipse(280, 80, 440,400);
	setcolor(RGB(0, 0, 255));
	ellipse(240, 80, 480, 400);
	ellipse(200, 120, 520,360);
	solidcircle(200,240,10);
	solidcircle(360, 80, 10);
	solidcircle(520, 240, 10);
	solidcircle(360, 400, 10);
	wchar_t cstr[256];
	LPTSTR str = cstr;
	InputBox(str, 256, L"Please input file name");
	setcolor(RGB(60, 125, 200));
	IMAGE img;
	loadimage(&img, str);
	int imgwid, imghei;
	imgwid = img.getwidth();
	imghei = img.getheight();
	if (imgwid == 0 && imghei == 0)
		exit(0);
	initgraph(imgwid, imghei);
	int dx = 0, dy = 0;
	int preimgwid, preimghei;
	preimgwid = imgwid;
	preimghei = imghei;
	int picshow = 0;
	while (1)
	{
		
		int c = GetCmd();
		if (c&CMD_UP)
			dy++;
		if (c&CMD_DOWN)
			dy--;
		if (c&CMD_LEFT)
			dx--;
		if (c&CMD_RIGHT)
			dx++;
		if (GetAsyncKeyState(VK_SPACE))
		{
			dx = 0; 
			dy = 0;
		}
		putimage(dx*preimgwid/1000, dy*preimghei/1000, &img);
		if (GetAsyncKeyState(VK_CONTROL))
		{
			Sleep(300);
			initgraph(imgwid, imghei);
		}
		
		if (GetAsyncKeyState(VK_MENU))
		{
			Sleep(300);
			initgraph(lines, cols);
		}
		if (GetAsyncKeyState(VK_PRIOR) || GetAsyncKeyState('X'))
		{
			picshow++;
			if (picshow > 50)
				picshow = 50;
			preimgwid = (int)(imgwid*(1 + (picshow)* 0.1));
			preimghei = (int)(imghei*(1 + (picshow)* 0.1));
			loadimage(&img, str, preimgwid, preimghei, true);
		}
		if (GetAsyncKeyState(VK_NEXT) || GetAsyncKeyState('Z'))
		{
			picshow--;
			if (picshow < -20)
				picshow = -20;
			preimgwid = (int)(imgwid*(1 + (picshow)* 0.05));
			preimghei = (int)(imghei*(1 + (picshow)* 0.05));
			loadimage(&img, str, preimgwid, preimghei, true);
		}
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			break;
		}
		if (GetAsyncKeyState('R'))
		{
			dx = 0;
			dy = 0;
			picshow = 0;
			loadimage(&img, str, imgwid, imghei,true);
		}
		

	}
	closegraph();
	return 0;
}

