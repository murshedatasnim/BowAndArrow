# include "iGraphics.h"
# include <math.h>
# include <time.h>
# include <stdlib.h>
# include <mmsystem.h>
# include <windows.h>
# define pi 3.1415926
# define g 9.8/100

int screenX = 1350, screenY = 680;
int initX=10, initY=145;
int arrowX=initX, arrowX2=arrowX+50, arrowY=initY, arrowY2=initY, t=0;
double q = 0, q2;
int v = 6, vx = v*cos(q*pi/180), vy = v*sin(q*pi/180);
int timeChange=1, timeMax, rmax;
int check=0,lexx=0;
int p, r, s, u;//timers
double Tx=1245, Ty=200, Tr=30, flag=0, flag2=0, TxRope=Tx+20;
int arrR=255, arrG=255, arrB=255;
int smallRecx=screenX/2-85, smallRecy=screenY-45, rsize=35;

int hit=0;
int iarrLeft = 11;
int vLineX1 = 12, vLineY1 = 510, vLength = 15, vLineY2 = vLineY1;

char score[5]={0}, highscore[20];
char level[1]={'1'};
int menu=1, iscore = 0, hitmode=7, missmode=0, gameover=0, intro=1;;
int keyflag=0;

bool soundOn = true;

char score1[3];
char score2[3];
char score3[3];
char score4[3];
char score5[3];
char score6[3];
char score7[3];
char score8[3];
char score9[3];
char score10[3];

char inputname[20];
int len;
//Score Structures
struct Highscores {
    char name[20];
    int score;
} scr[10];

/*struct Highscores scr[10] = {
    {"Aroni", 475},
    {"Freya", 450},
    {"Misha", 375},
    {"Auna", 370},
    {"Lex", 400},
    {"Rara", 425},
    {"Troy", 325},
    {"Zara", 350},
    {"Sherlock", 500},
    {"Gisly", 100}
};   */

void SortScores ()
{
    int i, j, n=10;
    struct Highscores temp;

    for (i=0; i<n; ++i)
        for (j=0; j<n-i-1; ++j)
        {
            if (scr[j].score <scr[j+1].score)
            {
                temp = scr[j];
                scr[j] = scr[j+1];
                scr[j+1] = temp;
            }
        }
}

void MoveTarget()
{
 if(Ty >= 610 || Ty <= 50) flag = !flag;

    if (flag) Ty+=3;
    else Ty-=3;
}

void MoveTargetFast()
{
 if(Ty >= 610 || Ty <= 50) flag = !flag;

    if (flag) Ty+=7;
    else Ty-=7;
}

void MoveTargetZigzag()
{
 if(Ty >= 620 || Ty <= 50) flag = !flag;
 if(Tx >= 1320 || Tx <= 1100) flag2 = !flag2;

    if (flag) Ty+=3.5;
    else Ty-=3.5;

    if (flag2) Tx+=3.5;
    else Tx-=3.5;
}

void MoveTargetZigzagFast()
{
 if(Ty >= 620 || Ty <= 50) flag = !flag;
 if(Tx >= 1320 || Tx <= 1100) flag2 = !flag2;

    if (flag) Ty+=6;
    else Ty-=6;

    if (flag2) Tx+=6;
    else Tx-=6;
}

void Lev1()
{
    Tx = 1245, Ty = 280;
}

void Lev2()
{
    MoveTarget();
}

void Lev3()
{
    MoveTargetFast();
}

void Lev4()
{
    TxRope=1210;
    MoveTargetZigzag();
}

void Lev5()
{
    TxRope=1210;
    MoveTargetZigzagFast();
}

void Hit()
{
     if (arrowX2>Tx && arrowX2<Tx+25 && arrowY2<(Ty+30) && arrowY2>Ty)
        {
           hitmode=1;
           iscore+=100;
           PlaySound("perfectshot", NULL, SND_ASYNC);
          arrowX=initX, arrowX2=arrowX+50, arrowY=initY, arrowY2=initY, timeChange = 1, timeMax = 0, check = 0, q=0;
        }
    if (arrowX2>(Tx+8) && arrowX2<(Tx+38) && ((arrowY2>(Ty+Tr)&& arrowY2<(Ty+Tr*2)) || ((arrowY2<Ty) && arrowY2>(Ty-Tr))))
    {
          hitmode=2;
          iscore+=50;
          PlaySound("niceon", NULL, SND_ASYNC);
          arrowX=initX, arrowX2=arrowX+50, arrowY=initY, arrowY2=initY, timeChange = 1, timeMax = 0, check = 0, q=0;
    }
    if (arrowX2>(Tx+16) && arrowX2<(Tx+46) && ((arrowY2>(Ty+Tr*2)&& arrowY2<(Ty+Tr*3)) || (arrowY2<(Ty-Tr) && arrowY2>(Ty-Tr*2))))
    {
          hitmode=3;
          iscore+=25;
          PlaySound("greatshot.wav", NULL, SND_ASYNC);
          arrowX=initX, arrowX2=arrowX+50, arrowY=initY, arrowY2=initY, timeChange = 1, timeMax = 0, check = 0, q=0;
    }
}

void Miss()
{
    if ((!hit) && (arrowY2<0 || arrowX2>screenX))
    {
       missmode=1;
        iarrLeft--;
        PlaySound("miss.wav", NULL, SND_ASYNC);
        arrowX=initX, arrowX2=arrowX+50, arrowY=initY, arrowY2=initY, timeChange = 1, timeMax = 0, check = 0, q=0;
    }
}

void HitMiss()
{
     if (hitmode==1)
        iShowBMP2(screenX/2-70, screenY/2, "100.bmp", 0);
        if (hitmode==2)
        iShowBMP2(screenX/2-40, screenY/2, "50.bmp",0);
        if (hitmode==3)
        iShowBMP2(screenX/2-40, screenY/2, "25.bmp",0);

      // if (missmode==1) iShowBMP2(screenX/2-40, screenY/2, "miss.bmp",0);
}
void Score()
{
        if (iscore<100)
        {
            level[0]='1';
            Lev1();
        }

    else if (iscore<200)
        {
            level[0]='2';
            Lev2();
        }
    else if (iscore<300)
      {
        level[0]='3';
        Lev3();
      }

     else if (iscore<400)
    {
        level[0]='4';
        Lev4();
    }
    else if (iscore<700)
    {
        level[0]='5';
        Lev5();
    }

    itoa(iscore, score, 10);

    if (iscore>=600 || iarrLeft==0)
    {
        gameover=1;
    }
}

void iDraw()
{
    iClear();

    if (iscore<100) {iShowBMP(0, 0, "tentforest.bmp"); arrR=255,arrG=255,arrB=230;}
    else if (iscore<200){iShowBMP(0, 0, "forestblue.bmp"); arrR=250,arrG=250,arrB=250;}
    else if (iscore<300){iShowBMP(0, 0, "forest3.bmp"); arrR=240,arrG=240,arrB=240;}
    else if (iscore<400){iShowBMP(0, 0, "darkforest.bmp"); arrR=240,arrG=240,arrB=240;}
    else if (iscore<600){iShowBMP(0, 0, "forestwater.bmp"); arrR=240,arrG=240,arrB=240;}

    if (iscore<600) //Until Game Over
    {
    //Speed/Direction & Bow
      iSetColor(240, 120, 100);
    iFilledCircle(-100, initY, 135);
      iSetColor(224,220,200);
    iFilledCircle(-100, initY, 127);

       iShowBMP(1270, 645,"menu.bmp");//60X20

    //Arrow
      iSetColor(arrR, arrG, arrB);
      iLine(arrowX, arrowY, arrowX2, arrowY2);
      iLine(arrowX-0.5, arrowY+0.5, arrowX2-0.5, arrowY2+0.5);

    //Target
    iSetColor(255,255,255);
    iLine(TxRope, screenY, Tx+20, Ty+75);
      iSetColor(255, 20, 20);
      iFilledRectangle(Tx, Ty, 8, Tr);
      iSetColor(250, 250, 100);
      iFilledRectangle(Tx+8, Ty-Tr, 8, Tr*3);
      iSetColor(105, 170, 255);
      iFilledRectangle(Tx+16, Ty-(Tr*2), 8, Tr*5);

      iSetColor(255,255,255);
      Hit();
      Miss();
      HitMiss();

     //Score
        itoa(iscore, score, 10);

        iSetColor(218,165,32); //ropes
        iLine(70, screenY-30, 70, screenY);
        iLine(71, screenY-30, 71, screenY);
        iLine(70+90, screenY-30, 70+90, screenY);
        iLine(70+90+1, screenY-30, 70+90+1, screenY);

        iLine(70+180, screenY-30, 70+180, screenY);
        iLine(71+180, screenY-30, 71+180, screenY);
        iLine(70+90+180, screenY-30, 70+90+180, screenY);
        iLine(70+90+1+180, screenY-30, 70+90+1+180, screenY);

        iShowBMP(44, screenY-45, "woodenboard.bmp");
        iShowBMP(44+180, screenY-45, "woodenboard.bmp");
        iShowBMP(42, screenY-95, "woodenboardlong.bmp");

        iSetColor(255,255,150);
        iFilledRectangle(vLineX1, vLineY1, vLength, 10);
        iText(13, 530, "SPEED", GLUT_BITMAP_HELVETICA_18);

        iSetColor(255,255,255);

        //BEHOLD THE ARROWS
        int arrLeftX=60, arrLeftY1=screenY-90, arrLeftY2=screenY-70, gap=26, i;

         if (iarrLeft>=1) iLine(arrLeftX, arrLeftY1, arrLeftX, arrLeftY2);//Arrow dandi
           for (i=1; i<=10; i++)
             if (iarrLeft>=(i+1)) iLine(arrLeftX+gap*i, arrLeftY1, arrLeftX+gap*i, arrLeftY2);

         if (iarrLeft>=1) iLine(arrLeftX-4, arrLeftY2-7, arrLeftX, arrLeftY2);//arrowhead left side
          for (i=1; i<=10; i++)
             if (iarrLeft>=(i+1)) iLine(arrLeftX-4+gap*i, arrLeftY2-7, arrLeftX+gap*i, arrLeftY2);

         if (iarrLeft>=1) iLine(arrLeftX, arrLeftY2, arrLeftX+4, arrLeftY2-7); // arrowhead right side
           for (i=1; i<=10; i++)
            if (iarrLeft>=(i+1)) iLine(arrLeftX+gap*i, arrLeftY2, arrLeftX+4+gap*i, arrLeftY2-7);

        iText (60, screenY-39, "SCORE :", GLUT_BITMAP_HELVETICA_18);
        iText (60+85, screenY-39, score, GLUT_BITMAP_HELVETICA_18);
        iText (60+180, screenY-39, "LEVEL : ", GLUT_BITMAP_HELVETICA_18);
        iText (60+260, screenY-39, level, GLUT_BITMAP_HELVETICA_18);

        //Pause-Restart
        iShowBMP(smallRecx, smallRecy, "pause.bmp");
        iShowBMP(smallRecx+rsize+20, smallRecy, "play.bmp");
        iShowBMP(smallRecx+rsize*2+20*2, smallRecy, "restart.bmp");
    }

        if (gameover==1)
        {
            iShowBMP(0, 0, "orangeforest.bmp");
            iShowBMP(screenX/2-250, screenY-220, "gameover.bmp");
            iShowBMP(1270, 645,"menu.bmp");//75X25

            if (iscore>=scr[9].score)
            {
                keyflag=1;
                iSetColor(250,250,210);
                iFilledRectangle(500, 250, 400, 150);
                iShowBMP(screenX/2-280, 220, "parchmentwide.bmp");
                iSetColor(0,0,0);
                iText(600, 330, "New High Score!", GLUT_BITMAP_TIMES_ROMAN_24);
                iText(590, 280, "Enter Your Name:", GLUT_BITMAP_HELVETICA_18);
                iText(760, 280, inputname, GLUT_BITMAP_HELVETICA_18);
                scr[9].score = iscore;
            }
            else gameover=2;
        }

        if (gameover==2)
        {
            iShowBMP(0, 0, "orangeforest.bmp");
            SortScores();
            iShowBMP(500, 30+70, "parchmentlong.bmp");
            iShowBMP(1270, 645,"menu.bmp");//75x25
             FILE *fp;
              fp = fopen("scores.txt", "w");
              int i;
                for (i=0; i<10; i++)
                  fprintf(fp, "%s\n%d\n", scr[i].name, scr[i].score);
                fclose(fp);

            iSetColor(0,0,0);

        if (menu!=2)
        {
            iShowBMP(screenX/2-250, screenY-185+70, "gameover.bmp");
            iText (580, 460+70, "Your Score : ", GLUT_BITMAP_HELVETICA_18);
            iText (710, 460+70, score, GLUT_BITMAP_HELVETICA_18);

            iShowBMP(585, 12,"exitbig.bmp");
            iShowBMP(585 , 54,"newgamesmall.bmp");//160X32
        }

            iText (620, 400+70, "Top Scores", GLUT_BITMAP_HELVETICA_18);
            iText (550, 360+70, scr[0].name, GLUT_BITMAP_HELVETICA_18);
            iText (550, 330+70, scr[1].name, GLUT_BITMAP_HELVETICA_18);
            iText (550, 300+70, scr[2].name, GLUT_BITMAP_HELVETICA_18);
            iText (550, 270+70, scr[3].name, GLUT_BITMAP_HELVETICA_18);
            iText (550, 240+70, scr[4].name, GLUT_BITMAP_HELVETICA_18);
            iText (550, 210+70, scr[5].name, GLUT_BITMAP_HELVETICA_18);
            iText (550, 180+70, scr[6].name, GLUT_BITMAP_HELVETICA_18);
            iText (550, 150+70, scr[7].name, GLUT_BITMAP_HELVETICA_18);
            iText (550, 120+70, scr[8].name, GLUT_BITMAP_HELVETICA_18);
            iText (550, 90+70, scr[9].name, GLUT_BITMAP_HELVETICA_18);

            itoa(scr[0].score, score1, 10); iText (750, 360+70, score1, GLUT_BITMAP_HELVETICA_18);
            itoa(scr[1].score, score2, 10); iText (750, 330+70, score2, GLUT_BITMAP_HELVETICA_18);
            itoa(scr[2].score, score3, 10); iText (750, 300+70, score3, GLUT_BITMAP_HELVETICA_18);
            itoa(scr[3].score, score4, 10); iText (750, 270+70, score4, GLUT_BITMAP_HELVETICA_18);
            itoa(scr[4].score, score5, 10); iText (750, 240+70, score5, GLUT_BITMAP_HELVETICA_18);
            itoa(scr[5].score, score6, 10); iText (750, 210+70, score6, GLUT_BITMAP_HELVETICA_18);
            itoa(scr[6].score, score7, 10); iText (750, 180+70, score7, GLUT_BITMAP_HELVETICA_18);
            itoa(scr[7].score, score8, 10); iText (750, 150+70, score8, GLUT_BITMAP_HELVETICA_18);
            itoa(scr[8].score, score9, 10); iText (750, 120+70, score9, GLUT_BITMAP_HELVETICA_18);
            itoa(scr[9].score, score10, 10);iText (750, 90+70, score10, GLUT_BITMAP_HELVETICA_18);
        }

        if (menu==3) {iShowBMP(0,0, "demo.bmp");}

	   if (menu==1)
    {
        iShowBMP(0,0,"orangeforest.bmp");
        iShowBMP(500, 450, "newgame.bmp");
        iShowBMP(500, 360, "highscores.bmp");
        iShowBMP(500, 270, "howtoplay.bmp");
        iShowBMP(500, 180, "about.bmp");
        iShowBMP(500, 90, "exit.bmp");
    }

        if (menu==4) {
                iShowBMP(0, 0, "aboutpage.bmp");
        iShowBMP(1270, 645,"menu.bmp");//75X25
        }

        if (hitmode==7) iShowBMP(0, 0, "intro.bmp");

}

void iMouseMove(int mx, int my)
{
	double a = mx-initX;
    double b = my-initY;

    q = atan2(b,a)*180/pi;

    vx = v*cos(q*pi/180);
    vy = v*sin(q*pi/180);
    rmax = v*v*sin(2*q*pi/180)/g;

    timeMax = v*sin(q*pi/180)/g;
    rmax = v*v*sin(2*q*pi/180)/g;

    arrowX2=arrowX + 50*cos(q*pi/180);
    arrowY2=arrowY + 50*sin(q*pi/180);
}

void iMouse(int button, int state, int mx, int my)
{

  if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
     if (menu==1)
        {
            if (mx>500 && mx<850 && my>450 && my<500)  //NewGame
            {
                menu=0;
                lexx=0;
                gameover=0;
                iscore = 0;
                iarrLeft = 11;
                TxRope = 1265;
            }

            if (mx>500 && mx<850 && my>360 && my<410)  //High Scores
            {
                gameover=2;
                menu=2;
            }

            if (mx>500 && mx<850 && my>270 && my<320) //HowToPlay
                {menu=3;}

            if (mx>500 && mx<850 && my>180 && my<230)
              menu = 4;

            if (mx>500 && mx<850 && my>90 && my<140)
              exit(1);
        }

        if (menu==0)
        {
            iResumeTimer(p);

                double a = mx-initX;
                double b = my-initY;

                q = atan2(b,a)*180/pi;

                vx = v*cos(q*pi/180);
                vy = v*sin(q*pi/180);
                rmax = v*v*sin(2*q*pi/180)/g;

                timeMax = v*sin(q*pi/180)/g;
                rmax = v*v*sin(2*q*pi/180)/g;

                arrowX2=arrowX + 50*cos(q*pi/180);
                arrowY2=arrowY + 50*sin(q*pi/180);

                if (mx>smallRecx && mx<smallRecx+35 && my>smallRecy && my<smallRecy+35)
                {
                    iPauseTimer(p);
                    iPauseTimer(r);
                    iPauseTimer(s);
                    lexx=0;
                }
                 if (mx>smallRecx+rsize+20 && mx<smallRecx+rsize+20+35 && my>smallRecy && my<smallRecy+35)
                 {
                    iResumeTimer(p);
                    iResumeTimer(r);
                    iResumeTimer(s);
                    lexx=0;
                 }
                 if (mx>smallRecx+rsize*2+20*2 && mx<smallRecx+rsize*2+20*2+35 && my>smallRecy && my<smallRecy+35)
                 {
                    gameover=0;
                    iscore = 0;
                    iarrLeft = 11;
                    TxRope = 1265;              //NEW GAME
                    lexx=0;
                 }
                 if (mx>1280 && mx<1340 && my>650 && my<670)
                    menu = 1;
            }
            if (menu)
                 if (mx>1270 && mx<1345 && my>645 && my<670)
                    menu = 1;

            if (gameover==2 && menu==0)
            {
                if (mx>585 && mx<585+160 && my>12 && my<12+32)//new game
                    exit(1);

                if (mx>585 && mx<585+160 && my>54 && my<54+32)//exit
                   { gameover=0;
                    iscore = 0;
                    iarrLeft = 11;
                    TxRope = 1265;              //NEW GAME
                    lexx=0;
                   }
            }

        }
           if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
            lexx++;
              if (lexx>1 && button == GLUT_LEFT_BUTTON && state == GLUT_UP)
              {
                 check=1;
                 PlaySound("arrow.wav", NULL, SND_ASYNC);
              }
                 if (menu) lexx=0;
}


void iKeyboard(unsigned char key)
{
	if(key==' ')
		check=1;

	if(key == 'r')
	{
	    iResumeTimer(p);
	    iResumeTimer(r);
	    iResumeTimer(s);
	}
	if (gameover!=1 &&  key=='m')
        menu=1;
        gameover=0;

	if (gameover==0 && key == 'p')
	{
	    iPauseTimer(p);
	    iPauseTimer(r);
	    iPauseTimer(s);
	}

    if (gameover!=1 && key=='c')
    {
        iscore = 425;
       iarrLeft = 1;
    }

    if (key>='a' && key<='z')
        iarrLeft--;

    if (keyflag==1)
    {
        gameover=1;

       if (key=='\r' || key=='\t')
       {
           strcpy(scr[9].name, inputname);
           keyflag = 0;
           gameover = 2;
        }

       else if (key=='\b' && len>0) inputname[--len]='\0';

       else
       { inputname[len]=key;
         len++;
       }
    }
}


void iSpecialKeyboard(unsigned char key)
{

	if(key == GLUT_KEY_END)
		exit(0);

	if (key == GLUT_KEY_RIGHT)
    {
        v++;
        if (vLength<=140) vLength+=9;
    }

    if (key == GLUT_KEY_LEFT)
    {
        v--;
        if (vLength>=10) vLength-=9;
    }
}

void Arrow()
{
    if (check == 1)
	{
	    arrowX = initX+(v*cos(q*pi/180)*timeChange);
        arrowY = initY+(arrowX*tan(q*pi/180) - 0.5*g*arrowX*arrowX /(v*cos(q*pi/180))/(v*cos(q*pi/180)));

        q2 = atan2(arrowY,arrowX);
        arrowX2 = arrowX+50*cos(q2);
        arrowY2 = initY+(arrowX2*tan(q*pi/180) - 0.5*g*arrowX2*arrowX2 /(v*cos(q*pi/180))/(v*cos(q*pi/180)));

        if (timeChange!=timeMax) timeChange++;

        if (arrowY<0)
        {
            timeChange = 1;
            timeMax = 0;
            check = 0;
        }
	}
}

void HitMode()
{
   hitmode=0;
   missmode=0;
}

int main()
{
    FILE *fp;
    int a = 0;

    fp = fopen("scores.txt", "r");
    if (fp==NULL)
    {
        printf("\nFile not found!\n\n");
        exit(0);
    }

    while(1)
    {
        if (feof(fp)) break; // if fp != EOF, go on.

        fscanf(fp, "%s%d", scr[a].name, &scr[a].score);
        printf("%s  %d\n", scr[a].name, scr[a].score);
        a++;
    }

    SortScores();

    p = iSetTimer(1, Arrow);
    s = iSetTimer(1, Score);
    r = iSetTimer(4000, HitMode);

    PlaySound("drum.wav", NULL, SND_ASYNC);
    iInitialize(screenX, screenY, "Arrow");

	return 0;
}
