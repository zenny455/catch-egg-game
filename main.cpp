#include <graphics.h>
#include <ctime>
#include <unistd.h>
#include <sstream>
#include <cstring>
#include <string>
#include <iostream>
#include <conio.h>
#include <fstream>
#include <mmsystem.h>
using namespace std;
int xgetRandomNumber()
{  
	int min=30,max=1055;
    return (min + rand() % (max - min + 1));  
} 
class s
{
	public:
		int score;
		s()
		{
			score=0; 
		}
};
int main()
{
	initwindow(1270,650);
	setbkcolor(WHITE);
	cleardevice();
	srand(time(0));
	int x1=480,x2=620,y1=510,y2=620;
	int e[4];
	for(int i=0;i<4;i++)
	{
		e[i]=0;
	}
	int xc[4],yc[4];
	int n=1;
	s ss;
	string sec="  ";
	string point="   ";
	time_t go,stop;
	int c;
	POINT cursor;
	
	setfillstyle(SOLID_FILL,RED);
	fillellipse(630,325,100,100);
	//square(530,225,730,425)
	
	//triangle
	setfillstyle(SOLID_FILL,GREEN);
	line(590,275,590,375);
	line(590,275,690,325);
	line(590,375,690,325);
	floodfill(630,325,WHITE);
	
	while(1)
	{
		if((GetAsyncKeyState(VK_LBUTTON))||(GetAsyncKeyState(VK_RBUTTON)))
		{
			GetCursorPos(&cursor);
			if(cursor.x-28>530 && cursor.x-28<730 && cursor.y-28>225 && cursor.y-28<425)
			{
				cleardevice();
				setcolor(BLUE);
				settextstyle(1,HORIZ_DIR,1);
				outtextxy(30,50,"YOU HAVE 60 seconds to CATCH the EGGS...!!!");
				delay(2000);
		
				time(&go);
	
				while(1)
				{
					time(&stop);
					c=difftime(stop,go);
					if(c==61)
					break;
		
					stringstream second;
					second<<c;
					second>>sec;
		
					setcolor(RED);
					settextstyle(4,HORIZ_DIR,2);
					outtextxy(1100,50,"TIME");
		
					outtextxy(1100,80,"00");
					outtextxy(1140,80,":");
					if(c<=9)
					{
						outtextxy(1155,80,"0");
						outtextxy(1175,80,(char*)sec.c_str());
					}	
					else
						outtextxy(1155,80,(char*)sec.c_str());
		
		
					for(int i=0;i<n;i++)
					{
						if(e[i]==0)
						{
							xc[i]=xgetRandomNumber();
							yc[i]=50;
							setcolor(YELLOW );
							setfillstyle(SOLID_FILL,YELLOW );
							fillellipse(xc[i],yc[i],25,40);
							e[i]=1;
						}
					}
		
					for(int i=0;i<n;i++)
					{
						yc[i]+=10;
						setcolor(YELLOW );
						setfillstyle(SOLID_FILL,YELLOW );
						fillellipse(xc[i],yc[i],25,40);
					}
			
					setcolor(RED);
					setlinestyle(0,0,3);
					rectangle(10,10,1080,620);
		
					setcolor(BLUE);
					setlinestyle(0,0,3);
					rectangle(x1,y1,x2,y2);
				
					setfillstyle(8,BLUE);
					bar(x1,y1,x2,y2);
			
					if(GetAsyncKeyState(VK_RIGHT))
					{
						x1+=20;
						x2+=20;
						if(x2>1080)
						{
							x2=1080;
							x1=x2-140;
						}
					}
		    		else if(GetAsyncKeyState(VK_LEFT))
					{
						x1-=20;
						x2-=20;
						if(x1<10)
						{
							x1=10;
							x2=x1+140;
						}
					}
					for(int i=0;i<n;i++)
					{
						if((xc[i]>x1 && xc[i]<x2) && yc[i]+20==y1+20)
						{
							e[i]=0;
							ss.score++;
							PlaySound(TEXT("score.wav"),NULL,SND_ASYNC);
							//system("pause");
						}
						else if((xc[i]>10 && xc[i]<1080 ) && yc[i]+40==620)
							e[i]=0;	
					}
		
					stringstream p;
					p<<ss.score;
					p>>point;
				
					setcolor(RED);
					settextstyle(4,HORIZ_DIR,2);
					outtextxy(1100,150,"POINTS");
					outtextxy(1100,180,(char*)point.c_str());
			
					delay(30);
			
					n++;
					if(n>4)
					{
						n=4;
					}
					cleardevice();
				}
				
				setcolor(RED);
				settextstyle(4,HORIZ_DIR,2);
				outtextxy(1100,50,"TIME");
		
				outtextxy(1100,80,"00");
				outtextxy(1140,80,":");
				if(c<=9)
				{
					outtextxy(1155,80,"0");
					outtextxy(1175,80,(char*)sec.c_str());
				}	
				else
					outtextxy(1155,80,(char*)sec.c_str());
	
				for(int i=0;i<n;i++)
				{
					yc[i]+=10;
					setcolor(YELLOW );
					setfillstyle(SOLID_FILL,YELLOW );
					fillellipse(xc[i],yc[i],25,40);
				}
		
				setcolor(RED);
				setlinestyle(0,0,3);
				rectangle(10,10,1080,620);
		
				setcolor(BLUE);
				setlinestyle(0,0,3);
				rectangle(x1,y1,x2,y2);
		
				setfillstyle(8,BLUE);
				bar(x1,y1,x2,y2);
		
	
				setcolor(RED);
				settextstyle(4,HORIZ_DIR,2);
				outtextxy(1100,150,"POINTS");
				outtextxy(1100,180,(char*)point.c_str());	
			}
			ofstream o("eggcatching.dat",ios::app);
			o.write((char*)&ss,sizeof(ss));
			o.close();
			s a;
			int max=ss.score;
			ifstream i("eggcatching.dat");
			while(i.read((char*)&a,sizeof(a)))
			{
				if(max<a.score)
					max=a.score;
			}
			if(max==ss.score)
				outtextxy(120,200,"New High Score");
			
			delay(5000);		
		}
		if(c==61)
			break;
	}
}
