//============================================================================
// Name        : game.cpp
// Author      : Syed Abdullah Nasir
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Dodge 'Em...
//============================================================================

#ifndef DODGE_CPP_
#define DODGE_CPP_
#include "util.h"
#include <iostream>
#include<string>
#include<fstream>
#include<cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;
float a_1=260; 
float b_1=30;
float a_2=500;
float b_2=30;
float a_3=740; 
float b_3=530;
int xx[1100][1100];
int xx_2[1100][1100];
int xx_3[1100][1100];
int score=0;
int liv=3;
int display=0;
int lev=1;
int gamescore[10]={184,180,150,145,160,140,120,110,83,80};
// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width,int height) 
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,width,0,height,-1,1); // set the screen size to given width and height.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
	
void displayinghighscore(int usertop)
{
	int high_Scores[10] ={184,180,150,145,160,140,120,110,83,30}; //scores array
	int t;
	//writing to a file
	ofstream fout;
	fout.open ("high score.txt"); //this function takes the name of the file that you are writing to
	if(usertop>high_Scores[9]){
		high_Scores[9]=usertop;
	}			   	
	int m=0;	
	while(m<10){
		int n=m+1;
		while(n<10){
			if(high_Scores[m]<high_Scores[n]){
				t=high_Scores[m];		
				high_Scores[m]=high_Scores[n];
				high_Scores[n]=t;
			}
			n++;
		}
		m++;
	}
	for (int i = 0; i < 10; i++){
		fout << high_Scores[i] << endl;
	}
	cout<<endl;
	
	fout.close();
	
	//reading from a file
	string score;
	ifstream fin ("high score.txt"); //name of the file it is supposed to read
	if (fin.is_open())
	{
		int m=0;
		int n=0;
		while ( getline (fin, score) ) //this loop will run depending on the number of lines in the file
		{
		 	cout << score << '\n';
		  	n=stoi(score);
		 	//HINT: use stoi() to convert string into Integer
			gamescore[m]=n;
			m++;
		  
		}
		fin.close();
	}
	
	else 
		cout << "Unable to open file"; 
	}

/*
 * Main Canvas drawing function.
 * */
//Board *b;
void GameDisplay()/**/
{
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(0.662745098039216,
				0.662745098039216, 0.662745098039216 ,0); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
	

	// calling some functions from util.cpp file to help students

	//Square at 400,20 position
	//DrawSquare( 400 , 20 ,40,colors[RED]); 
	//Square at 250,250 position
	//DrawSquare( 250 , 250 ,20,colors[GREEN]); 
	//Display Score
	//DrawString( 50, 800, "Score=0", colors[MISTY_ROSE]);
	//Triangle at 300, 450 position
	//DrawTriangle( 300, 450 , 340, 450 , 320 , 490, colors[MISTY_ROSE] ); 
	// Trianlge Vertices v1(300,50) , v2(500,50) , v3(400,250)
	//Circle at 50, 670 position
	//DrawCircle(50,670,10,colors[RED]);
	//Line from 550,50 to 550,480 with width 10
	//DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
	//DrawLine( 550 , 50 ,  550 , 480 , 10 , colors[MISTY_ROSE] );	
if(score==192 && display==1)
{
	display=6;
}
if(display==6)
{
	DrawString(300,400,"YOU WON THE GAME!!!!", colors[BLACK]);
	DrawString(480,10,"PRESS 'esc' key to close the game.", colors[BLACK]);
}
if(display==0)
{
	DrawString(50,700,"START GAME	[Press 'S' key to start the game.]", colors[BLACK]);
	DrawString(50,600,"RESUME	[Press 'R' key to resume the game once started.]", colors[BLACK]);
	DrawString(50,500,"HIGH SCORES	[Press '1' key to display high scores.]", colors[BLACK]);
	DrawString(50,400,"HELP	[Press 'H' key to show guide to the game.]", colors[BLACK]);
	DrawString(50,300,"EXIT	[Press 'esc' key to exit the game.]", colors[BLACK]);
}
if(display==4){
	int y=700,m=0;
	displayinghighscore(score);
	int q=1;
	while(m<10)
	{
		DrawString(00,750,"HIGH SCORES:", colors[BLACK]);
		DrawString(50,y,Num2Str(q)+":  "+Num2Str(gamescore[m]), colors[BLACK]);
		DrawString(480,10,"PRESS 'M' to go back to the menu.", colors[BLACK]);
		y-=60;
		q++;
		m++;
	}
}
if(display==3)
{
	DrawString( 350, 500, "YOU DIED", colors[RED]);
	DrawString( 100, 400, "TO PLAY AGAIN RELAUNCH THE GAME AFTER EXITTING", colors[BLACK]);
	DrawString( 350, 370, "USING 'esc' KEY", colors[BLACK]);
}
if(display==2)
{
	DrawString(0,850,"GUIDE:", colors[BLACK]);
	DrawString(0,800,"1.", colors[BLACK]);
	DrawString(70,700,"YOUR CAR", colors[BLACK]);
	DrawString(280,700,"OPPONENTS CAR", colors[BLACK]);
	DrawString(600,700,"POINTS", colors[BLACK]);
	DrawString(0,650,"2.This game involves your car(the blue one) to collect a series of points", colors[BLACK]);
	DrawString(0,620,"simultaneously dodging the opponents car(the red one) controlled by the",colors[BLACK]);
	DrawString(0,590,"computer.The opponents car follow artificial intelligence control following",colors[BLACK]);
	DrawString(0,560,"you everywher you go [EXCEPT THE SAFE ZONE PRESENT AT THE CENTER ",colors[BLACK]);
	DrawString(0,530,"OF THE SCREEN].This game involves 4 levels.",colors[BLACK]);
	DrawString(100,480,"LEVEL 1: In level 1, the opponents car will follow you but it will only", colors[BLACK]);
	DrawString(100,450,"enter the inner tracks from the upper and lower gaps present on the track.", colors[BLACK]);
	DrawString(100,400,"LEVEL 2: In level 2, the opponents car will follow you now being able to", colors[BLACK]);
	DrawString(100,370,"enter the inner tracks through gaps present all over the track,", colors[BLACK]);
	DrawString(100,340,"even through the gap present on the right and the left.", colors[BLACK]);
	DrawString(100,290,"LEVEL 3:In this level, the opponents car will call friend so there will be ", colors[BLACK]);
	DrawString(100,260,"two cars following you now.", colors[BLACK]);
	DrawString(0,180,"3.When you collect all the points you will move onto the next level immediately.", colors[BLACK]);
	DrawString(0,100,"4.Once you die,move the mouse pointer onto the screen for further instructions.", colors[BLACK]);
	DrawString(300,50,"BEST OF LUCK !!!!", colors[BLACK]);
	DrawString(480,10,"PRESS 'M' to go back to the menu.", colors[BLACK]);
	float x=0,y=0;
	DrawCircle(x+640,y+750,10,colors[BLACK]);
	// Drawing my car
		
	float width = 15; 
	float height = 10;
	float* color = colors[BLUE]; 
	float radius = 5.0;
	DrawRoundRect(x+100,y+750,width,height,color,radius); // bottom left tyre
	DrawRoundRect(x+100+width*3,y+750,width,height,color,radius); // bottom right tyre
	DrawRoundRect(x+100+width*3,y+750+height*4,width,height,color,radius); // top right tyre
	DrawRoundRect(x+100,y+height*4+750,width,height,color,radius); // top left tyre
	DrawRoundRect(x+100,y+height*2+750, width, height, color, radius/2); // body left rect
	DrawRoundRect(x+100+width,y+height+750, width*2, height*3, color, radius/2); // body center rect
	DrawRoundRect(x+100+width*3,y+height*2+750, width, height, color, radius/2); // body right rect
	
	// Drawing opponent car
	
	width = 15; 
	height = 10;
	float* color_1 = colors[MAROON]; 
	radius = 5.0;
	DrawRoundRect(x+350,y+750,width,height,color_1,radius); // bottom left tyre
	DrawRoundRect(x+350+width*3,y+750,width,height,color_1,radius); // bottom right tyre
	DrawRoundRect(x+350+width*3,y+height*4+750,width,height,color_1,radius); // top right tyre
	DrawRoundRect(x+350,y+height*4+750,width,height,color_1,radius); // top left tyre
	DrawRoundRect(x+350,y+height*2+750, width, height, color_1, radius/2); // body left rect
	DrawRoundRect(x+350+width,y+height+750, width*2, height*3, color_1, radius/2); // body center rect
	DrawRoundRect(x+350+width*3,y+height*2+750, width, height, color_1, radius/2); // body right rect
}
if(display==1)
{
	DrawString( 370,880, "LEVEL "+Num2Str(lev), colors[BLACK]);
	DrawString( 0,880, "TO PAUSE THE GAME", colors[BLACK]);
	DrawString( 70,860, "PRESS 'P'", colors[BLACK]);
	DrawString( 360, 400, "SAFE ZONE", colors[BLACK]);	
	DrawString( 450, 830, "SCORE = "+Num2Str(score), colors[BLACK]);
	if(lev==1)
	{
		for(int i=50;i<=800;i=i+103)
		{
			for(int j=50;j<=800;j=j+100)
			{	

				if(i>=400& i<=450)
				{
				}
				else
				{
					if(j>=400& j<=440)
					{
					}
					else
					{	
						if((i>=a_1-30&& i<=a_1+50) && (j>=b_1-20&& j<=b_1+50))
						{
							if(xx[i][j]!=1)
							{
								score=score+1;
							}
							xx[i][j]=1;	 
						}
					}
				}	
			}
		}
		for(int i=50;i<=800;i=i+103)
		{
			for(int j=50;j<=800;j=j+100)
			{	
				if(i>=400& i<=450)
				{
				}
				else
				{
					if(j>=400& j<=440)
					{
					}
					else
					{
						if(xx[i][j]==1)
						{
						}
						else
						{
							DrawCircle(i,j,10,colors[BLACK]);
						}
					}
				}		
			}
		}
	}
	if(score==64)
	{
		lev=2;
		a_1=260;
		a_2=500;
		b_2=30;
		b_1=30;
	}	
		if(lev==2)
		{ 
			for(int i=50;i<=800;i=i+103)
			{
				for(int j=50;j<=800;j=j+100)
				{	
	
					if(i>=400& i<=450)
					{
					}
					else
					{
						if(j>=400& j<=440)
						{
						}
						else
						{	
							if((i>=a_1-30&& i<=a_1+50) && (j>=b_1-20&& j<=b_1+50))
							{
								if(xx_2[i][j]!=1)
								{
									score=score+1;
								}
								xx_2[i][j]=1;	 
							}
						}
					}	
				}
			}
			for(int i=50;i<=800;i=i+103)
			{
				for(int j=50;j<=800;j=j+100)
				{	
					if(i>=400& i<=450)
					{
					}
					else
					{
						if(j>=400& j<=440)
						{
						}
						else
						{
							if(xx_2[i][j]==1)
							{
							}
							else
							{
								DrawCircle(i,j,10,colors[BLACK]);
							}
						}
					}		
				}
			}
		}
	if(score==128)
	{
		lev=3;
		a_1=260;
		a_2=500;
		b_2=30;
		b_1=30;
	}	
		if(lev==3)
		{ 
			for(int i=50;i<=800;i=i+103)
			{
				for(int j=50;j<=800;j=j+100)
				{	
	
					if(i>=400& i<=450)
					{
					}
					else
					{
						if(j>=400& j<=440)
						{
						}
						else
						{	
							if((i>=a_1-30&& i<=a_1+50) && (j>=b_1-20&& j<=b_1+50))
							{
								if(xx_3[i][j]!=1)
								{
									score=score+1;
								}
								xx_3[i][j]=1;	 
							}
						}
					}	
				}
			}
			for(int i=50;i<=800;i=i+103)
			{
				for(int j=50;j<=800;j=j+100)
				{	
					if(i>=400& i<=450)
					{
					}
					else
					{
						if(j>=400& j<=440)
						{
						}
						else
						{
							if(xx_3[i][j]==1)
							{
							}
							else
							{
								DrawCircle(i,j,10,colors[BLACK]);
							}
						}
					}		
				}
			}
		}
	if(lev==1 || lev==2)
	{
		// Drawing my car
		
		float width = 15; 
		float height = 10;
		float* color = colors[BLUE]; 
		float radius = 5.0;
		DrawRoundRect(a_1,b_1,width,height,color,radius); // bottom left tyre
		DrawRoundRect(a_1+width*3,b_1,width,height,color,radius); // bottom right tyre
		DrawRoundRect(a_1+width*3,b_1+height*4,width,height,color,radius); // top right tyre
		DrawRoundRect(a_1,b_1+height*4,width,height,color,radius); // top left tyre
		DrawRoundRect(a_1, b_1+height*2, width, height, color, radius/2); // body left rect
		DrawRoundRect(a_1+width, b_1+height, width*2, height*3, color, radius/2); // body center rect
		DrawRoundRect(a_1+width*3, b_1+height*2, width, height, color, radius/2); // body right rect
		
		// Drawing opponent car
		
		width = 15; 
		height = 10;
		float* color_1 = colors[MAROON]; 
		radius = 5.0;
		DrawRoundRect(a_2,b_2,width,height,color_1,radius); // bottom left tyre
		DrawRoundRect(a_2+width*3,b_2,width,height,color_1,radius); // bottom right tyre
		DrawRoundRect(a_2+width*3,b_2+height*4,width,height,color_1,radius); // top right tyre
		DrawRoundRect(a_2,b_2+height*4,width,height,color_1,radius); // top left tyre
		DrawRoundRect(a_2, b_2+height*2, width, height, color_1, radius/2); // body left rect
		DrawRoundRect(a_2+width, b_2+height, width*2, height*3, color_1, radius/2); // body center rect
		DrawRoundRect(a_2+width*3, b_2+height*2, width, height, color_1, radius/2); // body right rect
	}
	if(lev==3)
	{
		// Drawing my car
		
		float width = 15; 
		float height = 10;
		float* color = colors[BLUE]; 
		float radius = 5.0;
		DrawRoundRect(a_1,b_1,width,height,color,radius); // bottom left tyre
		DrawRoundRect(a_1+width*3,b_1,width,height,color,radius); // bottom right tyre
		DrawRoundRect(a_1+width*3,b_1+height*4,width,height,color,radius); // top right tyre
		DrawRoundRect(a_1,b_1+height*4,width,height,color,radius); // top left tyre
		DrawRoundRect(a_1, b_1+height*2, width, height, color, radius/2); // body left rect
		DrawRoundRect(a_1+width, b_1+height, width*2, height*3, color, radius/2); // body center rect
		DrawRoundRect(a_1+width*3, b_1+height*2, width, height, color, radius/2); // body right rect
		
		// Drawing opponent car
		
		width = 15; 
		height = 10;
		float* color_1 = colors[MAROON]; 
		radius = 5.0;
		DrawRoundRect(a_2,b_2,width,height,color_1,radius); // bottom left tyre
		DrawRoundRect(a_2+width*3,b_2,width,height,color_1,radius); // bottom right tyre
		DrawRoundRect(a_2+width*3,b_2+height*4,width,height,color_1,radius); // top right tyre
		DrawRoundRect(a_2,b_2+height*4,width,height,color_1,radius); // top left tyre
		DrawRoundRect(a_2, b_2+height*2, width, height, color_1, radius/2); // body left rect
		DrawRoundRect(a_2+width, b_2+height, width*2, height*3, color_1, radius/2); // body center rect
		DrawRoundRect(a_2+width*3, b_2+height*2, width, height, color_1, radius/2); // body right rect	
		
		// Drawing opponent car 2
		
		width = 15; 
		height = 10; 
		radius = 5.0;
		DrawRoundRect(a_3,b_3,width,height,color_1,radius); // bottom left tyre
		DrawRoundRect(a_3+width*3,b_3,width,height,color_1,radius); // bottom right tyre
		DrawRoundRect(a_3+width*3,b_3+height*4,width,height,color_1,radius); // top right tyre
		DrawRoundRect(a_3,b_3+height*4,width,height,color_1,radius); // top left tyre
		DrawRoundRect(a_3, b_3+height*2, width, height, color_1, radius/2); // body left rect
		DrawRoundRect(a_3+width, b_3+height, width*2, height*3, color_1, radius/2); // body center rect
		DrawRoundRect(a_3+width*3, b_3+height*2, width, height, color_1, radius/2); // body right rect	
	}

		//LIVES
		DrawString( 290, 830, "LIVES ="+Num2Str(liv), colors[BLACK]);	
		if(lev==1 || lev==2)
		{
			if((a_1>=a_2 && a_1<=a_2+30) && (b_1>=b_2 && b_1<=b_2+30))
			{
				a_1=200;
				a_2=500;
				b_1=30;
				b_2=30;
				if(liv>0)
				{
					liv=liv-1;
				}
			}
			
			if(liv==0)
			{
				DrawString( 380, 350, "DEAD", colors[RED]);
				display=3;			
			}
		}
		if(lev==3)
		{
			if((a_1>=a_2 && a_1<=a_2+30) && (b_1>=b_2 && b_1<=b_2+30))
			{
				a_1=200;
				a_2=500;
				b_1=30;
				b_2=30;
				a_3=740;
				b_3=530;
				if(liv>0)
				{
					liv=liv-1;
				}
			}
			if((a_1>=a_3 && a_1<=a_3+30) && (b_1>=b_3 && b_1<=b_3+30))
			{
				a_1=200;
				a_2=500;
				a_3=740;
				b_1=30;
				b_2=30;
				b_3=530;
				if(liv>0)
				{
					liv=liv-1;
				}
			}
			
			if(liv==0)
			{
				DrawString( 380, 350, "DEAD", colors[RED]);
				display=3;
			}
		}
			
		
		

		// Drawing Arena
		int gap_turn = 60;
		int sx = 20;
		int sy = 10;
		int swidth = 800/2 - gap_turn/2; // half width
		int sheight = 5;
		float *scolor = colors[BLACK];
		DrawRectangle(sx, sy, swidth, sheight, scolor); // bottom left
		DrawRectangle(sx + swidth + gap_turn, sy, swidth, sheight, scolor); // bottom right
		DrawRectangle(sx+swidth*2+gap_turn, sy+sheight, sheight*2, swidth, scolor); // right down
		DrawRectangle(sx+swidth*2+gap_turn, sy+sheight+swidth+gap_turn, sheight*2, swidth, scolor); // right up
		DrawRectangle(sx + swidth + gap_turn, sy+810, swidth, sheight, scolor); // top left
		DrawRectangle(sx, sy+810, swidth, sheight, scolor); // top right
		DrawRectangle(sx-sheight*2, sy+sheight+swidth+gap_turn, sheight*2, swidth, scolor); // left up
		DrawRectangle(sx-sheight*2, sy+sheight, sheight*2, swidth, scolor); // left down
		
		//First Rectangle
		//Left:
		DrawRectangle(sx+100, sy+100, swidth-150, sheight+10, scolor);//lower left horizontal
		DrawRectangle(sx+100, sy+100, swidth-390, sheight+180, scolor);//lower left vertical
		DrawRectangle(sx+100, sy+520, swidth-390, sheight+180, scolor);//upper left vertical
		DrawRectangle(sx+100, sy+690, swidth-150, sheight+10, scolor);//upper left horizontal
		//Right:
		DrawRectangle(sx+480, sy+100, swidth-150, sheight+10, scolor);//lower right horizontal
		DrawRectangle(sx+720, sy+100, swidth-390, sheight+180, scolor);//lower right vertical
		DrawRectangle(sx+720, sy+520, swidth-390, sheight+180, scolor);//upper right vertical
		DrawRectangle(sx+480, sy+690, swidth-150, sheight+10, scolor);//upper right horizontal	

		//Second Rectangle
		//Left:
		DrawRectangle(sx+210, sy+200, swidth-260, sheight+10, scolor);//lower left horizontal
		DrawRectangle(sx+210, sy+200, swidth-390, sheight+80, scolor);//lower left vertical
		DrawRectangle(sx+210, sy+590, swidth-260, sheight+10, scolor);//upper left horizontal
		DrawRectangle(sx+210, sy+520, swidth-390, sheight+80, scolor);//upper left vertical
		//Right:
		DrawRectangle(sx+480, sy+200, swidth-260, sheight+10, scolor);//lower right horizontal
		DrawRectangle(sx+610, sy+200, swidth-390, sheight+80, scolor);//lower right vertical
		DrawRectangle(sx+480, sy+590, swidth-260, sheight+10, scolor);//upper right horizontal
		DrawRectangle(sx+610, sy+520, swidth-390, sheight+80, scolor);//upper right vertical
		
		//Third Rectangle
		//Left:
		DrawRectangle(sx+320, sy+290, swidth-360, sheight+10, scolor);//lower left horizontal
		DrawRectangle(sx+320, sy+290, swidth-390, sheight+20, scolor);//lower left vertical
		DrawRectangle(sx+320, sy+500, swidth-360, sheight+10, scolor);//upper left horizontal
		DrawRectangle(sx+320, sy+490, swidth-390, sheight+20, scolor);//upper left vertical
		//Right:
		DrawRectangle(sx+460, sy+290, swidth-360, sheight+10, scolor);//lower right horizontal
		DrawRectangle(sx+490, sy+290, swidth-390, sheight+20, scolor);//lower right vertical
		DrawRectangle(sx+460, sy+500, swidth-360, sheight+10, scolor);//upper right horizontal
		DrawRectangle(sx+490, sy+490, swidth-390, sheight+20, scolor);//upper right vertical

}

	

	glutSwapBuffers(); // do not modify this line.. or draw anything below this line
}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) 
{
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>LEFT MOVEMENT[MY CAR]<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


	if(a_1==740 && b_1>=300 && b_1<=450)
	{
		if (key== GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/)// what to do when left key is pressed...
		{
			a_1=a_1-100;
			glutDisplayFunc(GameDisplay);
		}
	}
	

	else if(a_1==640 && b_1>=300 && b_1<=450)
	{
		if (key== GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/)// what to do when left key is pressed...
		{
			a_1=a_1-120;
			glutDisplayFunc(GameDisplay);
		}
		else if(key== GLUT_KEY_RIGHT)
		{
			a_1=a_1+100;
			glutDisplayFunc(GameDisplay);
		}
	}
	else if(a_1==520 && b_1>=300 && b_1<=450)
	{
		if (key== GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/)// what to do when left key is pressed...
		{
			a_1=a_1-90;
			glutDisplayFunc(GameDisplay);
		} 
		else if(key== GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) 
		{
			a_1=a_1+120;
			glutDisplayFunc(GameDisplay);
		}
	}

	if(a_1==340 && b_1>=300 && b_1<=450)
	{
		if (key== GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/)// what to do when left key is pressed...
		{
			a_1=a_1-100;
			glutDisplayFunc(GameDisplay);
		}
	}

	else if(a_1==240 && b_1>=300 && b_1<=450)
	{
		if (key== GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/)// what to do when left key is pressed...
		{
			a_1=a_1-120;
			glutDisplayFunc(GameDisplay);
		}
		else if(key== GLUT_KEY_RIGHT)
		{
			a_1=a_1+100;
			glutDisplayFunc(GameDisplay);
		}
	}


	else if(a_1==120 && b_1>=300 && b_1<=450)
	{
		if (key== GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/)// what to do when left key is pressed...
		{
			a_1=a_1-100;
			glutDisplayFunc(GameDisplay);
		}
		else if(key== GLUT_KEY_RIGHT)
		{
			a_1=a_1+120;
			glutDisplayFunc(GameDisplay);
		}
	}
	
	
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>RIGHT MOVEMENT[MY CAR]<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


	if(a_1==430 && b_1>=300 && b_1<=450)
	{ 
		if(key== GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) 
		{
			a_1=a_1+90;
			glutDisplayFunc(GameDisplay);
		}
	}
	if(a_1==20 && b_1>=300 && b_1<=450)
	{ 
		if(key== GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) 
		{
			a_1=a_1+100;
			glutDisplayFunc(GameDisplay);
		}
	}


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>UP MOVEMENT[MY CAR]<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 
	

	if(b_1==30 && a_1>=340 && a_1<=420)
	{
		if(key== GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) 
		{
			b_1=b_1+100;
			glutDisplayFunc(GameDisplay);
		}
	}


	else if(b_1==130 && a_1>=340 && a_1<=420)
	{
		if(key== GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) 
		{
			b_1=b_1+100;
			glutDisplayFunc(GameDisplay);
		}
		else if(key== GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for up arrow key*/) 
		{			
			b_1=b_1-100;
			glutDisplayFunc(GameDisplay);
		}
	}
	
	else if(b_1==230 && a_1>=340 && a_1<=480)
	{	
		if(key== GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) 
		{
			b_1=b_1+80;
			glutDisplayFunc(GameDisplay);
		}
		else if(key== GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for up arrow key*/) 
		{
			b_1=b_1-100;
			glutDisplayFunc(GameDisplay);
		}
	}
	if(b_1==460 && a_1>=340 && a_1<=420)
	{
		if(key== GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) 
		{
			b_1=b_1+60;
			glutDisplayFunc(GameDisplay);
		}
	}


	else if(b_1==520 && a_1>=340 && a_1<=420)
	{
		if(key== GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) 
		{
			b_1=b_1+100;
			glutDisplayFunc(GameDisplay);
		}
		else if(key== GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for up arrow key*/) 
		{			
			b_1=b_1-60;
			glutDisplayFunc(GameDisplay);
		}
	}
	

	else if(b_1==620 && a_1>=340 && a_1<=420)
	{
		if(key== GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) 
		{
			b_1=b_1+100;
			glutDisplayFunc(GameDisplay);
		}
		else if(key== GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for up arrow key*/) 
		{			
			b_1=b_1-100;
			glutDisplayFunc(GameDisplay);
		}
	}
	
		
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>DOWN MOVEMENT[MY CAR]<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	

	if(b_1==720 && a_1>=340 && a_1<=420)
	{	
		if(key== GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for up arrow key*/) 
		{
			b_1=b_1-100;
			glutDisplayFunc(GameDisplay);
		}
	}
	if(b_1==310 && a_1>=340 && a_1<=420)
	{	
		if(key== GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for up arrow key*/) 
		{
			b_1=b_1-80;
			glutDisplayFunc(GameDisplay);
		}
	}
	cout<<"a="<<a_1<<" and "<<"b="<<b_1<<endl;
	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/
	glutPostRedisplay();

}
void drive()
{
	if(display==1)
	{

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> MY CAR <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		//First Rectangle
		if(a_1>20 && b_1==30)
		{
			a_1=a_1-10;
		}
		else if(a_1==20 && b_1<720)
		{
			b_1=b_1+10;
		}	
		else if(a_1<740 && b_1==720)
		{
			a_1=a_1+10;
		}
		else if(a_1==740 && b_1>30)
		{
			b_1=b_1-10;
		}	

		//Second Rectangle
		else if(a_1>120 && b_1==130)
		{
			a_1=a_1-10;
		}
		else if(a_1==120 && b_1<620)
		{
			b_1=b_1+10;
		}	
		else if(a_1<640 && b_1==620)
		{
			a_1=a_1+10;
		}
		else if(a_1==640 && b_1>130)
		{
			b_1=b_1-10;
		}

		//Third Rectangle
		else if(a_1>240 && b_1==230)
		{
			a_1=a_1-10;
		}
		else if(a_1==240 && b_1<520)
		{
			b_1=b_1+10;
		}	
		else if(a_1<520 && b_1==520)
		{
			a_1=a_1+10;
		}
		else if(a_1==520 && b_1>230)
		{
			b_1=b_1-10;
		}

		//Fourth Rectangle
		else if(a_1>340 && b_1==310)
		{
			a_1=a_1-10;
		}
		else if(a_1==340 && b_1<460)
		{
			b_1=b_1+10;
		}	
		else if(a_1<430 && b_1==460)
		{
			a_1=a_1+10;
		}
		else if(a_1==430 && b_1>310)
		{
			b_1=b_1-10;
		}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> SECOND CAR <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		//First Rectangle
		if(a_2<740 && b_2==30)
		{
			a_2=a_2+10;
		}
		else if(a_2==740 && b_2<720)
		{
			b_2=b_2+10;
		}	
		else if(a_2>20 && b_2==720)
		{
			a_2=a_2-10;
		}
		else if(a_2==20 && b_2>30)
		{
			b_2=b_2-10;
		}	

		//Second Rectangle
		else if(a_2<640 && b_2==130)
		{
			a_2=a_2+10;
		}
		else if(a_2==640 && b_2<620)
		{
			b_2=b_2+10;
		}	
		else if(a_2>120 && b_2==620)
		{
			a_2=a_2-10;
		}
		else if(a_2==120 && b_2>130)
		{
			b_2=b_2-10;
		}

		//Third Rectangle
		else if(a_2<520 && b_2==230)
		{
			a_2=a_2+10;
		}
		else if(a_2==520 && b_2<520)
		{
			b_2=b_2+10;
		}	
		else if(a_2>240 && b_2==520)
		{
			a_2=a_2-10;
		}
		else if(a_2==240 && b_2>230)
		{
			b_2=b_2-10;
		}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> THIRD CAR <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		//First Rectangle
		if(a_3<740 && b_3==30)
		{
			a_3=a_3+10;
		}
		else if(a_3==740 && b_3<720)
		{
			b_3=b_3+10;
		}	
		else if(a_3>20 && b_3==720)
		{
			a_3=a_3-10;
		}
		else if(a_3==20 && b_3>30)
		{
			b_3=b_3-10;
		}	

		//Second Rectangle
		else if(a_3<640 && b_3==130)
		{
			a_3=a_3+10;
		}
		else if(a_3==640 && b_3<620)
		{
			b_3=b_3+10;
		}	
		else if(a_3>120 && b_3==620)
		{
			a_3=a_3-10;
		}
		else if(a_3==120 && b_3>130)
		{
			b_3=b_3-10;
		}

		//Third Rectangle
		else if(a_3<520 && b_3==230)
		{
			a_3=a_3+10;
		}
		else if(a_3==520 && b_3<520)
		{
			b_3=b_3+10;
		}	
		else if(a_3>240 && b_3==520)
		{
			a_3=a_3-10;
		}
		else if(a_3==240 && b_3>230)
		{
			b_3=b_3-10;
		}
	if(lev==1)
	{
		//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> AI MOVEMENT   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	
		//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> INWARD <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		if((a_1==120 || a_1<=640) && (b_1==130 || b_1==620))
		{
			if(b_2==30 && a_2>=340 && a_2<=420)//UP
			{
				b_2=b_2+100;
				glutDisplayFunc(GameDisplay);
			}
			if(b_2==720 && a_2>=340 && a_2<=420)//DOWN
			{
				b_2=b_2-100;
				glutDisplayFunc(GameDisplay);
			}
		}	
		if((a_1==240 || a_1==520) && (b_1==230 || b_1==520))
		{
			if(b_2==130 && a_2>=340 && a_2<=420)//UP
			{
				b_2=b_2+100;
				glutDisplayFunc(GameDisplay);
			}
			if(b_2==620 && a_2>=340 && a_2<=420)//DOWN
			{
				b_2=b_2-100;
				glutDisplayFunc(GameDisplay);
			}	
		}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> OUTWARD <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		if((a_1==20 || a_1<=740) && (b_1==30 || b_1==720))
		{
			if(b_2==130 && a_2>=340 && a_2<=420)//DOWN
			{
				b_2=b_2-100;
				glutDisplayFunc(GameDisplay);
			}
			if(b_2==620 && a_2>=340 && a_2<=420)//UP
			{
				b_2=b_2+100;
				glutDisplayFunc(GameDisplay);
			}
		}
		if((a_1==140 || a_1==640) && (b_1==130 || b_1==620))
		{
			if(b_2==230 && a_2>=340 && a_2<=420)//UP
			{
				b_2=b_2-100;
				glutDisplayFunc(GameDisplay);
			}
			if(b_2==520 && a_2>=340 && a_2<=420)//DOWN
			{
				b_2=b_2+100;
				glutDisplayFunc(GameDisplay);
			}
		}
		
	}
	if(lev==2)
	{
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> AI MOVEMENT <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> INWARD <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		if((a_1==120 || a_1<=640) && (b_1==130 || b_1==620))
		{
			if(a_2==740 && b_2>=300 && b_2<=450)//LEFT
			{
				a_2=a_2-100;
				glutDisplayFunc(GameDisplay);
			}
			if(a_2==20 && b_2>=300 && b_2<=450)//RIGHT
			{ 
				a_2=a_2+100;
				glutDisplayFunc(GameDisplay);	
			}
			if(b_2==30 && a_2>=340 && a_2<=420)//UP
			{
				b_2=b_2+100;
				glutDisplayFunc(GameDisplay);
			}
			if(b_2==720 && a_2>=340 && a_2<=420)//DOWN
			{
				b_2=b_2-100;
				glutDisplayFunc(GameDisplay);
			}
		}	
		if((a_1==240 || a_1==520) && (b_1==230 || b_1==520))
		{
			if(a_2==640 && b_2>=300 && b_2<=450)//LEFT
			{
				a_2=a_2-120;
				glutDisplayFunc(GameDisplay);
			}
			if(a_2==120 && b_2>=300 && b_2<=450)//RIGHT
			{ 
				a_2=a_2+120;
				glutDisplayFunc(GameDisplay);	
			}
			if(b_2==130 && a_2>=340 && a_2<=420)//UP
			{
				b_2=b_2+100;
				glutDisplayFunc(GameDisplay);
			}
			if(b_2==620 && a_2>=340 && a_2<=420)//DOWN
			{
				b_2=b_2-100;
				glutDisplayFunc(GameDisplay);
			}	
		}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> OUTWARD <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		if((a_1==20 || a_1<=740) && (b_1==30 || b_1==720))
		{
			if(a_2==640 && b_2>=300 && b_2<=450)//RIGHT
			{
				a_2=a_2+100;
				glutDisplayFunc(GameDisplay);
			}
			if(a_2==120 && b_2>=300 && b_2<=450)//LEFT
			{ 
				a_2=a_2-100;
				glutDisplayFunc(GameDisplay);	
			}
			if(b_2==130 && a_2>=340 && a_2<=420)//DOWN
			{
				b_2=b_2-100;
				glutDisplayFunc(GameDisplay);
			}
			if(b_2==620 && a_2>=340 && a_2<=420)//UP
			{
				b_2=b_2+100;
				glutDisplayFunc(GameDisplay);
			}
		}
		if((a_1==140 || a_1==640) && (b_1==130 || b_1==620))
		{
			if(a_2==520 && b_2>=300 && b_2<=450)//LEFT
			{
				a_2=a_2+120;
				glutDisplayFunc(GameDisplay);
			}
			if(a_2==240 && b_2>=300 && b_2<=450)//RIGHT
			{ 
				a_2=a_2-120;
				glutDisplayFunc(GameDisplay);	
			}
			if(b_2==230 && a_2>=340 && a_2<=420)//UP
			{
				b_2=b_2-100;
				glutDisplayFunc(GameDisplay);
			}
			if(b_2==520 && a_2>=340 && a_2<=420)//DOWN
			{
				b_2=b_2+100;
				glutDisplayFunc(GameDisplay);
			}
		}
	}
	if(lev==3)
	{
		if((a_1==120 || a_1<=640) && (b_1==130 || b_1==620))
		{
			if(a_2==740 && b_2>=300 && b_2<=450)//LEFT
			{
				a_2=a_2-100;
				glutDisplayFunc(GameDisplay);
			}
			if(a_2==20 && b_2>=300 && b_2<=450)//RIGHT
			{ 
				a_2=a_2+100;
				glutDisplayFunc(GameDisplay);	
			}
			if(b_2==30 && a_2>=340 && a_2<=420)//UP
			{
				b_2=b_2+100;
				glutDisplayFunc(GameDisplay);
			}
			if(b_2==720 && a_2>=340 && a_2<=420)//DOWN
			{
				b_2=b_2-100;
				glutDisplayFunc(GameDisplay);
			}
		}	
		if((a_1==240 || a_1==520) && (b_1==230 || b_1==520))
		{
			if(a_2==640 && b_2>=300 && b_2<=450)//LEFT
			{
				a_2=a_2-120;
				glutDisplayFunc(GameDisplay);
			}
			if(a_2==120 && b_2>=300 && b_2<=450)//RIGHT
			{ 
				a_2=a_2+120;
				glutDisplayFunc(GameDisplay);	
			}
			if(b_2==130 && a_2>=340 && a_2<=420)//UP
			{
				b_2=b_2+100;
				glutDisplayFunc(GameDisplay);
			}
			if(b_2==620 && a_2>=340 && a_2<=420)//DOWN
			{
				b_2=b_2-100;
				glutDisplayFunc(GameDisplay);
			}	
		}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> OUTWARD <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		if((a_1==20 || a_1<=740) && (b_1==30 || b_1==720))
		{
			if(a_2==640 && b_2>=300 && b_2<=450)//RIGHT
			{
				a_2=a_2+100;
				glutDisplayFunc(GameDisplay);
			}
			if(a_2==120 && b_2>=300 && b_2<=450)//LEFT
			{ 
				a_2=a_2-100;
				glutDisplayFunc(GameDisplay);	
			}
			if(b_2==130 && a_2>=340 && a_2<=420)//DOWN
			{
				b_2=b_2-100;
				glutDisplayFunc(GameDisplay);
			}
			if(b_2==620 && a_2>=340 && a_2<=420)//UP
			{
				b_2=b_2+100;
				glutDisplayFunc(GameDisplay);
			}
		}
		if((a_1==140 || a_1==640) && (b_1==130 || b_1==620))
		{
			if(a_2==520 && b_2>=300 && b_2<=450)//LEFT
			{
				a_2=a_2+120;
				glutDisplayFunc(GameDisplay);
			}
			if(a_2==240 && b_2>=300 && b_2<=450)//RIGHT
			{ 
				a_2=a_2-120;
				glutDisplayFunc(GameDisplay);	
			}
			if(b_2==230 && a_2>=340 && a_2<=420)//UP
			{
				b_2=b_2-100;
				glutDisplayFunc(GameDisplay);
			}
			if(b_2==520 && a_2>=340 && a_2<=420)//DOWN
			{
				b_2=b_2+100;
				glutDisplayFunc(GameDisplay);
			}
		}
		//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> AI MOVEMENT 2nd AI<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		if((a_1==120 || a_1<=640) && (b_1==130 || b_1==620))
		{
			if(a_3==740 && b_3>=300 && b_3<=450)//LEFT
			{
				a_3=a_3-100;
				glutDisplayFunc(GameDisplay);
			}
			if(a_3==20 && b_3>=300 && b_3<=450)//RIGHT
			{ 
				a_3=a_3+100;
				glutDisplayFunc(GameDisplay);	
			}
			if(b_3==30 && a_3>=340 && a_3<=420)//UP
			{
				b_3=b_3+100;
				glutDisplayFunc(GameDisplay);
			}
			if(b_3==720 && a_3>=340 && a_3<=420)//DOWN
			{
				b_3=b_3-100;
				glutDisplayFunc(GameDisplay);
			}
		}	
		if((a_1==240 || a_1==520) && (b_1==230 || b_1==520))
		{
			if(a_3==640 && b_3>=300 && b_3<=450)//LEFT
			{
				a_3=a_3-120;
				glutDisplayFunc(GameDisplay);
			}
			if(a_3==120 && b_3>=300 && b_3<=450)//RIGHT
			{ 
				a_3=a_3+120;
				glutDisplayFunc(GameDisplay);	
			}
			if(b_3==130 && a_3>=340 && a_3<=420)//UP
			{
				b_3=b_3+100;
				glutDisplayFunc(GameDisplay);
			}
			if(b_3==620 && a_3>=340 && a_3<=420)//DOWN
			{
				b_3=b_3-100;
				glutDisplayFunc(GameDisplay);
			}	
		}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> OUTWARD <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		if((a_1==20 || a_1<=740) && (b_1==30 || b_1==720))
		{
			if(a_3==640 && b_3>=300 && b_3<=450)//RIGHT
			{
				a_3=a_3+100;
				glutDisplayFunc(GameDisplay);
			}
			if(a_3==120 && b_3>=300 && b_3<=450)//LEFT
			{ 
				a_3=a_3-100;
				glutDisplayFunc(GameDisplay);	
			}
			if(b_3==130 && a_3>=340 && a_3<=420)//DOWN
			{
				b_3=b_3-100;
				glutDisplayFunc(GameDisplay);
			}
			if(b_3==620 && a_3>=340 && a_3<=420)//UP
			{
				b_3=b_3+100;
				glutDisplayFunc(GameDisplay);
			}
		}
		if((a_1==140 || a_1==640) && (b_1==130 || b_1==620))
		{
			if(a_3==520 && b_3>=300 && b_3<=450)//LEFT
			{
				a_3=a_3+120;
				glutDisplayFunc(GameDisplay);
			}
			if(a_3==240 && b_3>=300 && b_3<=450)//RIGHT
			{ 
				a_3=a_3-120;
				glutDisplayFunc(GameDisplay);	
			}
			if(b_3==230 && a_3>=340 && a_3<=420)//UP
			{
				b_3=b_3-100;
				glutDisplayFunc(GameDisplay);
			}
			if(b_3==520 && a_3>=340 && a_3<=420)//DOWN
			{
				b_3=b_3+100;
				glutDisplayFunc(GameDisplay);
			}
		}
	}
	glutDisplayFunc(GameDisplay);
	glutPostRedisplay();
}

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) 
{
	if (key == 27/* Escape key ASCII*/) 
	{
		exit(1); // exit the program when escape key is pressed.
	}
	if((key=='p' || key=='P') && display==1)
	{
		display=0;
	}
	else if(key=='m' || key=='M')
	{
		display=0;
	}
	else if((key=='s' || key=='S') && display==0)
	{
		display=1;
	}
	else if((key=='r' || key=='R') && display==0)
	{
		display=1;
	}
	else if((key=='h' || key=='H') && display==0)
	{
		display=2;
	}
	else if(key=='1' && (display==4 || display==0))
	{
		display=4;
	}
	


	glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) 
{

	// implement your functionality here

	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(1000.0, Timer, 0);
}

/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y) 
{
	cout << x << " " << y << endl;
	glutPostRedisplay();
}
void MouseMoved(int x, int y) 
{

	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) 
{

	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
	{
		cout << GLUT_DOWN << " " << GLUT_UP << endl;
	}
	else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
	{
	}
	glutPostRedisplay();
}
/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {

	//b = new Board(60, 60); // create a new board object to use in the Display Function ...

	int width = 840, height = 900; // i have set my window size to be 800 x 600
	//b->InitalizeBoard(width, height);
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("NEED FOR SPEED::THE STONE AGE"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...
	glutIdleFunc(drive);

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.

	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* AsteroidS_CPP_ */
