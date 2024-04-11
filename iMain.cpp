#include "iGraphics.h"
#include <string.h>
#include <math.h>

int pen = 0, eraser = 0, colorWheel = 0, move = 0, copy = 0, text = 0, thick = 0, shape = 0, save = 0, penLine = 0, penLine2 = 0;

int white_mode = 0, dark_mode = 0;  //create

int move_byX, move_byY;

int penRed = 0, penGreen = 0, penBlue = 0;
int bgRed = 255, bgGrn = 255, bgBlue = 255;
int eraserRed = 255, eraserGrn = 255, eraserBlue = 255;
int bmpX = 50, bmpY = 205;
int textBoxX, textBoxY, textBox = 0, textInd = 0, textRed = 0, textCount = 0, textflag = 0;
char txtArr[5][100];
int penThick = 4;
int tSldX = 75, tSldY = 362;
int rectangle = 0, circle = 0, line = 0, recX, recY, recL, recB;
int ptsX = 0, ptsY = 0;
int peniconX = -100, peniconY = -100, erasericonX = -100, erasericonY = -100, erasericonR = penThick;

int copyRX1, copyRY1, copyRX2, copyRY2;

int linePoint = 0, lineArr[600][7], lineVar = 1;

int penArr[20000][6], rectArr[100][5], circArr[100][5]; // x y red grn blue thick
int penPoint = 0, circPoint = 0, rectPoint = 0, eraserPoint = 0, textPoint = 0, copyMove = 0;

struct write
{
	int wx, wy;
	char txt[100];
};

struct write note[40];

struct copy_rec
{
	int cx1, cy1, cx2, cy2;
};

struct copy_rec copyRec;

int page1 = 1, page2 = 0; //instruction

/*
	function iDraw() is called again and again by the system.

	*/

void iDraw()
{

	iClear();

	if (page1)
	{
		
		iSetColor(255, 255, 255); // background
		iFilledRectangle(0, 0, 1500, 750);
		iFilledRectangle(450, 250, 80, 50);
		iShowBMP(0, 0, "rsz_11whiteboards2.bmp");
		iShowBMP(800, 50, "name.bmp");

		iSetColor(0, 0, 255);
		iLine(750, 150, 750, 350);
		iSetColor(200, 200, 200);
		//iFilledRectangle(150, 250, 250, 50);

		iSetColor(0, 0, 0);
		iFilledRectangle(580, 250, 80, 50);
		iRectangle(450, 250, 80, 50);
		iText(455, 220, "White", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(585, 220, "Dark", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(180, 263, "CREATE BOARD    ==>", GLUT_BITMAP_TIMES_ROMAN_24);
	}

	if (page2)
	{
		iSetColor(bgRed, bgGrn, bgBlue); // background
		iFilledRectangle(0, 0, 1500, 750);

		eraserRed = bgRed;
		eraserGrn = bgGrn;
		eraserBlue = bgBlue;

		if(dark_mode)
		{
			textRed=255;
		}

		


		for (int i = 1; i < penPoint; i++)
		{

			iSetColor(penArr[i][2], penArr[i][3], penArr[i][4]);
			iFilledCircle(penArr[i][0], penArr[i][1], penArr[i][5]);
		}

		iSetColor(penRed, penGreen, penBlue);
		for (int i = 0; i < textCount; i++)
		{

			iText(note[i].wx, note[i].wy, note[i].txt, GLUT_BITMAP_TIMES_ROMAN_24);
		}
		for (int i = 1; i < rectPoint; i++)
		{

			iSetColor(rectArr[i][2], rectArr[i][3], rectArr[i][4]);
			iRectangle(rectArr[i][0], rectArr[i][1], 70, 70);
		}

		for (int i = 1; i < circPoint; i++)
		{

			iSetColor(circArr[i][2], circArr[i][3], circArr[i][4]);
			iCircle(circArr[i][0], circArr[i][1], 30);
		}

		for (int i = 0; i < linePoint; i++)
		{

			iSetColor(lineArr[i][4], lineArr[i][5], lineArr[i][6]);
			iLine(lineArr[i][0], lineArr[i][1], lineArr[i][2], lineArr[i][3]);
		}

		if (colorWheel)
		{
			iShowBMP(70, 380, "Free-Color-Selection-Tools (1).bmp");
		}

		if (textBox)
		{
			iSetColor(textRed, bgGrn, bgBlue);
			iRectangle(textBoxX, textBoxY, textInd * 12 + 100, 40);
		}
		iSetColor(255, 255, 255);
		iFilledRectangle(20, 260, 40, 40);
		iSetColor(220,220,220);
		//iFilledRectangle(1450,700,30,30);  // ? instructions

		iShowBMP(20, 460, "depositphotos_469717486-stock-illustration-write-pencil-pen-icon.bmp"); // pen
		iShowBMP(20, 420, "eraser-icon-vector-42997666.bmp");
		iShowBMP(20, 340, "line-width-icon-vector-19399279 (1).bmp");
		iShowBMP(20, 300, "images_(1).bmp");
		iShowBMP(20, 220, "text-type-tool-icon.bmp");
		iShowBMP(20, 180, "Untitled (4).bmp");
		iShowBMP(25, 265, "copy (1).bmp");

		if (pen)
		{
			iShowBMP2(peniconX, peniconY, "free-pen-366-458834.bmp", 16777215);
		}
		else if (eraser)
		{

			iSetColor(255, 255, 255);
			iFilledCircle(erasericonX, erasericonY, penThick);
			iSetColor(0, 0, 0);
			iCircle(erasericonX, erasericonY, penThick);
		}

		if (copy)
		{
			iSetColor(0, 255, 0);
			iRectangle(copyRec.cx1, copyRec.cy1, copyRec.cx2 - copyRec.cx1, copyRec.cy2 - copyRec.cy1);
			iSetColor(255, 0, 0);
			iFilledRectangle(copyRec.cx1 - 5, copyRec.cy1, 10, 10);
		}
		iSetColor(255, 255, 255);
		iFilledRectangle(20, 380, 40, 40); // colour select

		iSetColor(0, 0, 0);
		//iText(1458,705,"?",GLUT_BITMAP_TIMES_ROMAN_24);
		iRectangle(20, 220, 40, 40); // text
		iRectangle(20, 460, 40, 40); // pen
		iRectangle(20, 420, 40, 40); // eraser
		iRectangle(20, 380, 40, 40); // color select
		iRectangle(20, 340, 40, 40); // thickness
		iRectangle(20, 300, 40, 40); // move
		iRectangle(20, 260, 40, 40); // copy
		iRectangle(20, 180, 40, 40); // shape

		if (shape)
		{

			iShowBMP(70, 180, "rec.bmp");	// R
			iShowBMP(110, 180, "circ.bmp"); // C
			iShowBMP(150, 180, "line.bmp"); // L
			iRectangle(70, 180, 40, 40);	// rectangle
			iRectangle(110, 180, 40, 40);	// circle
			iRectangle(150, 180, 40, 40);	// line
		}

		iSetColor(penRed, penGreen, penBlue);
		iFilledCircle(40, 400, 13);

		iSetColor(255, 0, 0);

		if (colorWheel)
		{
			iRectangle(20, 380, 40, 40);
		}
		else if (move)
		{
			
			iRectangle(20, 300, 40, 40);
		}
		else if (eraser)
		{
			iRectangle(20, 420, 40, 40);
		}
		else if (pen)
		{
			iRectangle(20, 460, 40, 40);
		}
		else if (thick)
		{
			iRectangle(20, 340, 40, 40);
		}
		else if (copy)
		{

			iRectangle(20, 260, 40, 40);
		}
		else if (text)
		{
			iRectangle(20, 220, 40, 40);
		}

		else if (shape)
		{
			iRectangle(20, 180, 40, 40);
			if (rectangle)
			{
				iRectangle(70, 180, 40, 40);
			}
			else if (line)
			{
				iRectangle(150, 180, 40, 40);
			}
			else if (circle)
			{
				iRectangle(110, 180, 40, 40);
			}
		}

		iSetColor(0, 0, 0);

		if (thick)
		{
			iSetColor(200, 200, 200);
			iFilledRectangle(70, 350, 115, 25); // thickness levels
			iSetColor(0, 0, 0);
			iLine(70, 362, 70 + 100, 362);
			iFilledCircle(tSldX, tSldY, 6);
		}

		if(move)
		{
			iShowBMP(600,680,"moveIns.bmp");
		}
		if(copy)
		{
			iShowBMP(530,630,"copyIns.bmp");
		}
		if(text)
		{
			iShowBMP(530,680,"textIns.bmp");
		}
	}

	// place your drawing codes here
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouseMove(int mx, int my)
{
	printf("x = %d, y= %d\n", mx, my);
	if (page2)
	{
		
		

		if (pen)
		{
			penArr[penPoint][0] = mx, penArr[penPoint][1] = my; // x y red grn blue thick
			penArr[penPoint][2] = penRed, penArr[penPoint][3] = penGreen, penArr[penPoint][4] = penBlue;
			penArr[penPoint][5] = penThick;
			peniconX = mx, peniconY = my;
			penPoint++;
		}

		if (copyMove)
		{
			copyRec.cx2 += mx - copyRec.cx1;
			copyRec.cy2 += my - copyRec.cy1;
			copyRec.cx1 = mx;
			copyRec.cy1 = my;
		}

		if (eraser)
		{
			penArr[penPoint][0] = mx, penArr[penPoint][1] = my; // x y red grn blue thick
			penArr[penPoint][2] = bgRed, penArr[penPoint][3] = bgGrn, penArr[penPoint][4] = bgBlue;
			penArr[penPoint][5] = penThick;
			erasericonX = mx, erasericonY = my;
			penPoint++;
		}
		if (thick)
		{

			if (mx >= 75 && mx <= 175 && my >= 350 && my <= 370)
			{

				tSldX = mx;
				penThick = (mx - 75) / 10 + 2;
				printf("%c\n", thick);

				if (thick == 'p')
				{
					thick++;
				}
				else if (thick == 'e')
				{
					thick--;
				}
			}

			else if (thick > 'p')
			{
				printf("%c", thick);
				pen = 1;
				thick = 0;
			}
			else
			{
				eraser = 1;
				thick = 0;
			}
		}

		if (line)
		{
			iLine(lineArr[linePoint - 1][0], lineArr[linePoint - 1][1], mx, my);
		}
	}
	// place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouse(int button, int state, int mx, int my)
{
	if (page2)
	{

		
		
		if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		{
			if (line && !(mx >= 20 && mx <= 60 && my >= 180 && my <= 500) && !(mx >= 70 && mx <= 190 && my >= 180 && my <= 220))
			{
				lineArr[linePoint][2] = mx, lineArr[linePoint][3] = my;
				lineArr[linePoint][4] = penGreen, lineArr[linePoint][5] = penGreen, lineArr[linePoint][6] = penBlue;

				linePoint++;
			}
			peniconX = -100, peniconY = -100, erasericonX = -100, erasericonY = -100;
			if (pen)
			{
				penLine = 0, penLine2 = 0;
			}
			if (copy)
			{

				copyRec.cx2 = mx;
				copyRec.cy2 = my;
				printf("%d %d\n", copyRec.cx2, copyRec.cy2);

				if (copyRec.cx1 < copyRec.cx2)
				{
					copyRX1 = copyRec.cx1, copyRX2 = copyRec.cx2;
				}
				else
				{
					copyRX1 = copyRec.cx2, copyRX2 = copyRec.cx1;
				}
				if (copyRec.cy1 < copyRec.cy2)
				{
					copyRY1 = copyRec.cy1, copyRY2 = copyRec.cy2;
				}
				else
				{
					copyRY1 = copyRec.cy2, copyRY2 = copyRec.cy1;
				}
			}
		}
		if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
		{

			if (copyMove)
			{
				int copyTemp = penPoint;
				for (int i = 0; i < copyTemp; i++)
				{
					if ((penArr[i][0]) >= copyRX1 && (penArr[i][0]) <= copyRX2 && (penArr[i][1]) >= copyRY1 && (penArr[i][1]) <= copyRY2)
					{
						penArr[penPoint + 1][0] = penArr[i][0] + mx - copyRX1;
						penArr[penPoint + 1][1] = penArr[i][1] + my - copyRY2;
						penArr[penPoint + 1][2] = penArr[i][2], penArr[penPoint + 1][3] = penArr[i][3], penArr[penPoint + 1][4] = penArr[i][4];
						penArr[penPoint + 1][5] = penArr[i][5];
						penPoint++;
					}
				}

				copyMove = 0;
			}
		}
		if (rectangle)
		{
			if (!(mx >= 20 && mx <= 60 && my >= 180 && my <= 500) && !(mx >= 70 && mx <= 190 && my >= 180 && my <= 220))
			{
				rectArr[rectPoint][0] = mx, rectArr[rectPoint][1] = my;
				rectArr[rectPoint][2] = penRed, rectArr[rectPoint][3] = penGreen, rectArr[rectPoint][4] = penBlue;
				rectPoint++;
			}
		}
		if (circle)
		{
			if (!(mx >= 20 && mx <= 60 && my >= 180 && my <= 500) && !(mx >= 70 && mx <= 190 && my >= 180 && my <= 220))
			{
				circArr[circPoint][0] = mx, circArr[circPoint][1] = my;
				circArr[circPoint][2] = penRed, circArr[circPoint][3] = penGreen, circArr[circPoint][4] = penBlue;
				circPoint++;
			}
		}
		if (line && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			if (!(mx >= 20 && mx <= 60 && my >= 180 && my <= 500) && !(mx >= 70 && mx <= 190 && my >= 180 && my <= 220))
			{
				printf("3");
				lineArr[linePoint][0] = mx, lineArr[linePoint][1] = my;
			}
		}
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			// place your codes here
			//	printf("x = %d, y= %d\n",mx,my);
			if (pen)
			{
				penLine = 1;
			}
			if (copy)
			{

				copyRec.cx1 = mx;
				copyRec.cy1 = my;
				printf("%d %d\n", copyRec.cx1, copyRec.cy1);
			}
			if (mx >= 20 && mx <= 60 && my >= 300 && my <= 340)
			{
				copy = 0, shape = 0, save = 0;
				move = 1;
			}
			if (mx >= 20 && mx <= 60 && my >= 460 && my <= 500)
			{
				move = 0, copy = 0, shape = 0, save = 0;
				eraser = 0, thick = 0, rectangle = 0, text = 0; // selecting pen
				pen = 1;
			}

			if (mx >= 20 && mx <= 60 && my >= 500 && my <= 540)
			{
				move = 0, copy = 0, shape = 0;
				eraser = 0, thick = 0, rectangle = 0, text = 0, pen = 0; // selecting save
				save = 1;
			}
			if (mx >= 20 && mx <= 60 && my >= 420 && my <= 460)
			{
				move = 0, copy = 0, shape = 0, save = 0, colorWheel = 0;
				pen = 0, thick = 0, text = 0;
				eraser = 1; // selecting eraser
			}

			if (mx >= 20 && mx <= 60 && my >= 220 && my <= 260)
			{
				move = 0, copy = 0, shape = 0, save = 0;
				thick = 0;
				pen = 0;
				eraser = 0;

				text = 1;
			}

			if (text)
			{
				if (!(mx >= 20 && mx <= 60 && my >= 180 && my <= 500))
					textBox = 1;
				else
					textBox = 0;
				textBoxX = mx, textBoxY = my, textRed = 0;
				note[textPoint].wx = textBoxX + 14, note[textPoint].wy = textBoxY + 14, note[textPoint].txt[0] = 0;
			}
			if (mx >= 20 && mx <= 60 && my >= 180 && my <= 220)
			{
				pen = 0, eraser = 0, colorWheel = 0, move = 0, copy = 0, text = 0, thick = 0, save = 0;
				shape = 1;
			}

			if ((pen || eraser) && mx >= 20 && mx <= 60 && my >= 340 && my <= 380)
			{
				colorWheel = 0;
				if (pen)
				{
					thick = 'p';
				}
				else if (eraser)
				{
					thick = 'e';
				}
				pen = 0, eraser = 0;
			}

			if (mx >= 20 && mx <= 60 && my >= 380 && my <= 420 && pen)
			{
				move = 0, copy = 0, shape = 0, save = 0, thick = 0;
				colorWheel = 1;
			}

			if (colorWheel)
			{
				// colorCalled = true; // selecting pen colour
				if (mx >= 70 && mx <= 470 && my >= 380 && my <= 540)
				{
					colorWheel = 2;
					int pixArray[3] = {255, 0, 0};
					iGetPixelColor(mx, my, pixArray);
					penRed = pixArray[0];
					penGreen = pixArray[1];
					penBlue = pixArray[2];

					// bmpX=-220;
				}
				else if (colorWheel == 2)
				{
					colorWheel = 0;
				}
			}
			if (mx >= 20 && mx <= 60 && my >= 260 && my <= 300)
			{
				pen = 0, eraser = 0, colorWheel = 0, move = 0, shape = 0, text = 0, thick = 0, save = 0;
				copy = 1;
				// zoom_num*=1.2;
				//  for (int m = 0; m < penPoint; m++)
				//  {

				// 	penArr[m][0]-=10; //textPoint=0

				// }
			}
			if (text == 1 && !(mx >= 20 && mx <= 60 && my >= 180 && my <= 500) && textflag)
			{
				textPoint++;
				printf("%d %s %d\n", textPoint, note[textPoint - 1].txt, textInd); // textPoint=0
				printf("%s\n", note[textPoint - 1].txt);
				// note[textPoint].txt[textInd]=0;
				textflag = 0;
				textInd = 0;
				textRed = bgRed;
			}
			if (shape) // && (mx<=20 || mx>=190 || my<=180 || my>=220)
			{
				if (mx >= 70 && mx <= 110 && my <= 220 && my >= 180)
				{
					rectangle = 1, line = 0, circle = 0;
					// printf("hhh");
				}
				else if (mx >= 110 && mx <= 150 && my <= 220 && my >= 180)
				{
					circle = 1, rectangle = 0, line = 0;
				}
				else if (mx >= 150 && mx <= 190 && my <= 220 && my >= 180)
				{
					line = 1, rectangle = 0, circle = 0;
					printf("hhh");
				}
			}
			else
			{
				line = 0, rectangle = 0, circle = 0;
			}
		}
		if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		{
			if (copy && mx >= copyRec.cx1 - 5 && mx <= copyRec.cx1 + 5 && my >= copyRec.cy1 && my <= copyRec.cy1 + 10)
			{
				copyMove = 1; // copyRec.cx1-5, copyRec.cy1,10,10
			}
		}
	}
	else if (page1)
	{
		if (mx >= 450 && mx <= 530 && my >= 250 && my <= 300) // 450,250,80,50
		{
			white_mode = 1;
			page1 = 0;
			page2 = 1;
		}
		else if (mx >= 580 && mx <= 660 && my >= 250 && my <= 300) // 580,250,80,50
		{
			dark_mode = 1;
			bgRed = 0, bgGrn = 0, bgBlue = 0;
			page1 = 0;
			page2 = 1;
			penRed = 255, penGreen = 255, penBlue = 255;
		}
	}
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
	*/
void iKeyboard(unsigned char key)
{

	if (page2)
	{

		if (key == 'z')
		{
			FILE *fptr;
			fptr = fopen("bruh.txt", "wb");
			fwrite(penArr, sizeof(int), sizeof(penArr), fptr);
		}
		if (textBox == 1 && text == 1)
		{

			if (key == '\r')
			{
				// note[textPoint].txt[textInd]=0;
				textflag = 0;

				// text = 0;
				textInd = 0;
				
				if(dark_mode)
					textRed=0;
				else textRed = bgRed;

				textPoint++;
			}
			else if (key == '\b')
			{
				if (textInd <= 0)
				{
					textInd = 0;
				}
				else
					textInd--;

				note[textPoint].txt[textInd] = 0;
			}
			else
			{
				// note[textPoint].txt[textInd]=0;
				// textPoint++;

				// note[textPoint].wx=textBoxX + 14,note[textPoint].wy=textBoxY + 14;
				textflag = 1;
				note[textPoint].txt[textInd] = key;
				note[textPoint].txt[textInd + 1] = 0;
				textInd++;
				//

				// textPoint++;
				if (textInd == 1)
					textCount++;
			}
		}
	}
	// place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
	*/
void iSpecialKeyboard(unsigned char key)
{
	if (page2)
	{
		if (key == GLUT_KEY_END)
		{
			exit(0);
		}
		if (move)
		{
			if (key == GLUT_KEY_RIGHT)
			{

				move_byX -= 10;
				for (int i = 0; i < penPoint; i++)
				{

					penArr[i][0] -= 10;
				}
				for (int i = 0; i < rectPoint; i++)
				{

					rectArr[i][0] -= 10;
				}
				for (int i = 0; i < circPoint; i++)
				{

					circArr[i][0] -= 10;
				}

				for (int i = 0; i < textCount; i++)
				{

					note[i].wx -= 10;
				}
				for (int i = 0; i < linePoint; i++)
				{

					lineArr[i][0] -= 10, lineArr[i][2] -= 10;
				}
			}

			else if (key == GLUT_KEY_LEFT)
			{

				move_byX += 10;
				for (int i = 0; i < penPoint; i++)
				{

					penArr[i][0] += 10;
				}
				for (int i = 0; i < rectPoint; i++)
				{

					rectArr[i][0] += 10;
				}
				for (int i = 0; i < circPoint; i++)
				{

					circArr[i][0] += 10;
				}
				for (int i = 0; i < textCount; i++)
				{

					note[i].wx += 10;
				}
				for (int i = 0; i < linePoint; i++)
				{

					lineArr[i][0] += 10, lineArr[i][2] += 10;
				}
			}

			else if (key == GLUT_KEY_UP)
			{

				move_byY -= 10;
				for (int i = 0; i < penPoint; i++)
				{

					penArr[i][1] -= 10;
				}
				for (int i = 0; i < rectPoint; i++)
				{

					rectArr[i][1] -= 10;
				}
				for (int i = 0; i < circPoint; i++)
				{

					circArr[i][1] -= 10;
				}
				for (int i = 0; i < textCount; i++)
				{

					note[i].wy -= 10;
				}
				for (int i = 0; i < linePoint; i++)
				{

					lineArr[i][1] -= 10, lineArr[i][3] -= 10;
				}
			}

			else if (key == GLUT_KEY_DOWN)
			{
				move_byY += 10;
				for (int i = 0; i < penPoint; i++)
				{

					penArr[i][1] += 10;
				}
				for (int i = 0; i < rectPoint; i++)
				{

					rectArr[i][1] += 10;
				}
				for (int i = 0; i < circPoint; i++)
				{

					circArr[i][1] += 10;
				}
				for (int i = 0; i < textCount; i++)
				{

					note[i].wy += 10;
				}
				for (int i = 0; i < linePoint; i++)
				{

					lineArr[i][1] += 10, lineArr[i][3] += 10;
				}
			}
		}
	}

	// place your codes for other keys here
}

int main()
{

	// place your own initialization codes here.
	// int t=iSetTimer(5,colorSelector);
	// lineArr[0][0] = 0, lineArr[0][1] = 0, lineArr[0][2] = 0, lineArr[0][3] = 0;
	// note[0].txt[0]=0;
	// struct copy_rec copyRec;

	iInitialize(1500, 750, "Whiteboard");

	return 0;
}




//textbox color