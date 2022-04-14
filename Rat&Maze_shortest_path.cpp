//Works fine without adding the walls
#include <graphics.h>
#include <stdio.h>
#include <windows.h>
#include <bits/stdc++.h>

using namespace std;

//Welcome page
void welcome()
{
    for(int i=0;i<=250;i+=10)
    {
        setcolor(MAGENTA);
        settextstyle(3,HORIZ_DIR,5);
        outtextxy(i+50,50,"WELCOME TO THE MAZE!");
        settextstyle(3,HORIZ_DIR,4);
        outtextxy(i+200,150,"Done by:");
        setcolor(WHITE);
        outtextxy(i+100,200,"Lakshan H");
        delay(50);
        cleardevice();
    }
    setcolor(MAGENTA);
    settextstyle(3,HORIZ_DIR,5);
    rectangle(320,30,880,100);
    outtextxy(350,50,"WELCOME TO THE MAZE!");
    settextstyle(3,HORIZ_DIR,4);
    outtextxy(550,150,"Done by:");
    setcolor(WHITE);
    outtextxy(540,200,"Lakshan H");
    delay(300);
    setcolor(RED);
    rectangle(380,380,810,440);
    outtextxy(400,390,"Press any key to continue !");
    getch();
    cleardevice();
}

//Filling the color at the right position
fillcolour(int y,int x,int c,int s=50)
{
    if((x%2==0)&&(y%2==0))
    {
        x=x/2;y=y/2;
        setfillstyle(1,c);
        floodfill((x*100+70),(y*100+20),CYAN);
        delay(s);
        return 0;
    }
    if((x%2==0)&&(y%2!=0))
    {
        x=x/2;y=y/2+1;
        setfillstyle(1,c);
        floodfill((x*100+70),(y*100-20),CYAN);
        delay(s);
        return 0;
    }
    if((x%2!=0)&&(y%2==0))
    {
        x=x/2+1;y=y/2;
        setfillstyle(1,c);
        floodfill((x*100+20),(y*100+20),CYAN);
        delay(s);
        return 0;
    }
    if((x%2!=0)&&(y%2!=0))
    {
        x=x/2+1;y=y/2+1;
        setfillstyle(1,c);
        floodfill((x*100+20),(y*100-20),CYAN);
        delay(s);
        return 0;
    }
}

//Finding the right index to fill the walls and start/end
int position(int n)
{
    int arr[2];
    int flag=0,r;
    while(n>0 && flag<2)
    {
        r=n%10;
        arr[flag]=r;
        flag++;
        n=n/10;
    }
    return arr[1];
}

//Setting up the maze and finding path
void getmaze(int row,int col)
{
    int str_end=0,str_x,str_y,end_x,end_y;
    int ar[20][20];
    int mark[20][20];
    int x_pos,y_pos,num,flag=0,r;
    //Building walls
    for(int i=0;i<row+2;i++)
    {
        for(int j=0;j<col+2;j++)
        {
           if(i==0 && j>=0 && j<col+2)
                ar[i][j]=1;
            else if(i>=0 && i<row+2 && j==0)
                ar[i][j]=1;
            else if(i==row+1 && j>=0 && j<col+2)
                ar[i][j]=1;
            else if(i>=0 && i<row+2 && j==col+1)
                ar[i][j]=1;
            else
                ar[i][j]=0;
        }
    }
    //Building maze
    for(int i=0;i<=row+2;i++)
    {
        for(int j=0;j<=col+2;j++)
        {
            setcolor(CYAN);
            if(i!=row+2)
                line(((j*50)+100),50,((j*50)+100),((i*50)+100));//vertical lines
            if(j!=col+2)
                line(100,((i*50)+50),((j*50)+150),((i*50)+50));//horizontal lines
        }
    }
    //Building walls in the maze
    for(int i=0;i<=row+2;i++)
    {
        for(int j=0;j<=col+2;j++)
        {
            if(i==0 && j>=0 && j<col+2)
                fillcolour(i+1,j+1,4);
            else if(i>=0 && i<row+2 && j==0)
                fillcolour(i+1,j+1,4);
            else if(i==row+1 && j>=0 && j<col+2)
                fillcolour(i+1,j+1,4);
            else if(i>=0 && i<row+2 && j==col+1)
                fillcolour(i+1,j+1,4);
            else
                continue;
        }
    }
    //Instructions : Left click to set the starting/ending position
    rectangle(800,50,950,100);
    setfillstyle(1,GREEN);
    floodfill(820,70,CYAN);
    settextstyle(8,HORIZ_DIR,2);
    outtextxy(820,65,"LEFT CLICK");
    settextstyle(8,HORIZ_DIR,1);
    outtextxy(1000,65," - START / END ");
    //Right click to set the walls
    rectangle(800,150,960,200);
    setfillstyle(1,RED);
    floodfill(820,170,CYAN);
    settextstyle(8,HORIZ_DIR,2);
    outtextxy(820,165,"RIGHT CLICK");
    settextstyle(8,HORIZ_DIR,1);
    outtextxy(1000,165," - WALLS ");

    //Setting up walls,start/end position
    POINT pos;
    while(1)
    {
        GetCursorPos(&pos);
        if(GetAsyncKeyState(VK_RBUTTON))
        {

            x_pos= pos.x/100;
            if(position(pos.x)>=5)
                x_pos=x_pos*2;
            else
                x_pos=(x_pos*2)-1;

            y_pos= pos.y/100;
            if(y_pos==0)
                y_pos=1;
            else if(position(pos.y)>=5)
                y_pos=(y_pos*2)+1;
            else
                y_pos=y_pos*2;

            ar[y_pos-1][x_pos-1]=1;
            setfillstyle(1,RED);
            floodfill(pos.x,pos.y,CYAN);
        }
        delay(100);
        if(GetAsyncKeyState(VK_LBUTTON) && str_end<2)
        {
            x_pos= pos.x/100;
            if(position(pos.x)>=5)
                x_pos=x_pos*2;
            else
                x_pos=(x_pos*2)-1;

            y_pos= pos.y/100;
            if(y_pos==0)
                y_pos=1;
            else if(position(pos.y)>=5)
                y_pos=(y_pos*2)+1;
            else
                y_pos=y_pos*2;

            ar[y_pos-1][x_pos-1]=2;
            setfillstyle(1,GREEN);
            floodfill(pos.x,pos.y,CYAN);
            if(str_end==0)
                {str_x=y_pos-1;str_y=x_pos-1;}
            if(str_end==1)
                {end_x=y_pos-1;end_y=x_pos-1;}

            str_end+=1;
        }
        delay(100);
        //Setting up a start button
        if(str_end==2)
        {
            rectangle(800,500,950,600);
            settextstyle(BOLD_FONT,HORIZ_DIR,3);
            outtextxy(830,530,"Start");
            break;
        }
        delay(100);
    }
    while(1)
    {
        GetCursorPos(&pos);
        //Starting to find the path when the start button is clicked
        if(GetAsyncKeyState(VK_LBUTTON))
        {
            if(pos.x>810 && pos.x<949 && pos.y>530 && pos.y<630)
              {
                  for(int i=0;i<row+2;i++)
                    {
                        for(int j=0;j<col+2;j++)
                            mark[i][j]=ar[i][j];
                    }
                int queue[row*col][3]={str_x,str_y,0},f=-1,l=0,i,j;
                int dir=0,g,h,flag=0;
                vector< vector<long long> > v;
                int move[8][2]={{0,1},{1,0},{0,-1},{-1,0},{-1,1},{1,1},{1,-1},{-1,-1}};
                vector<long long> t;
                t.push_back(1);
                t.push_back(1);
                t.push_back(0);
                v.push_back(t);

                int a=0;
                while(f!=l)
                {
                    f=f+1;
                    i=queue[f][0];
                    j=queue[f][1];
                    dir=0;
                    while(dir<=7)
                    {
                        g=i+move[dir][0];
                        h=j+move[dir][1];
                        if((g==end_x)&&(h==end_y))
                        {
                            vector<long long> temp;
                            temp.push_back(g);
                            temp.push_back(h);
                            long long x=100*v[a][2]+10*queue[f][0]+queue[f][1];
                            temp.push_back(x);
                            v.push_back(temp);
                            int n=v.size();
                            //long long X=v[n-1][2];
                            long long r;
                            vector<long long> d;
                            while(x>0)
                            {
                                r=x%10;
                                d.push_back(r);
                                x=x/10;
                            }
                            reverse(d.begin(), d.end());
                            for(int i=0;i<d.size();i+=2)
                            {
                                fillcolour(d[i]+1,d[i+1]+1,14,500);
                            }
                            rectangle(800,250,1150,350);
                            settextstyle(8,HORIZ_DIR,4);
                            outtextxy(880,280,"PATH FOUND");
                            return;
                        }
                        if((ar[g][h]==0)&&(mark[g][h]==0))
                        {
                            mark[g][h]+=1;l=l+1;
                            vector<long long> temp;
                            temp.push_back(g);
                            temp.push_back(h);
                            int x=(100*v[a][2])+(10*queue[f][0])+(queue[f][1]);
                            temp.push_back(x);
                            v.push_back(temp);
                            queue[l][0]=g;
                            queue[l][1]=h;
                            queue[l][2]=dir;
                        }
                        dir=dir+1;
                    }
                    a++;
                }
                break;

            }
            delay(100);
        }
    }
    //Path not found message
    rectangle(800,250,1150,350);
    settextstyle(8,HORIZ_DIR,4);
    outtextxy(850,280,"PATH NOT FOUND");
    return;
}

int main()
{
    int row=0,col=0;
    printf("Enter number of rows(max 10):");
    scanf("%d",&row);
    printf("Enter number of columns(max 10):");
    scanf("%d",&col);

    //Setting the max resolution of the output screen
    DWORD ScrWidth = GetSystemMetrics(SM_CXSCREEN);
    DWORD ScrHeight = GetSystemMetrics(SM_CYSCREEN);
    initwindow(ScrWidth,ScrHeight, NULL);

    //Welcome message
    welcome();
    //Running the program until exit is pressed
    POINT pos;
    while(1)
    {
        getmaze(row,col);
        //Setting up exit and reset buttons
        rectangle(1000,500,1150,600);
        settextstyle(BOLD_FONT,HORIZ_DIR,3);
        outtextxy(1030,530,"Exit");
        rectangle(900,400,1080,450);
        settextstyle(BOLD_FONT,HORIZ_DIR,2);
        outtextxy(950,410,"RESET");
        while(1)
        {
            GetCursorPos(&pos);
            if(GetAsyncKeyState(VK_LBUTTON))
            {
                if(pos.x>905 && pos.x<1080 && pos.y>420 && pos.y<470)
                {
                    cleardevice();
                    break;
                }
                if(pos.x>1010 && pos.x<1149 && pos.y>530 && pos.y<630)
                    exit(0);
            }
            delay(100);
        }
        delay(100);
    }
    getch();
    closegraph();
}


