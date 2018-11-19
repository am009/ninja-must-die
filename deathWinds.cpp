#include <graphics.h>
#include <stdio.h>
#define LENTH 640
#define HEIGHT 480
#define FLOOR 250
#define FLOORHEIGHT 10
#define MAN 150


void init()
{

}

void mainloop()
{
	//x,y记录当前位置，dx,dy记录速度向量，r记录圆半径
	int x[7];
	int dx = 200;
	int upDown = 0;//0是上，1是下。
	key_msg k = {0};
    int i, j;//for循环用的
    int death = 0 ;//死亡的次数
    int score = 0 ;
    int scoreCopy = -2;
    //注意去初始化一下初始位置。
    x[0] = 620;
    x[1] = 500;
    //x[2] = 690;
    //x[4] = 800;


	for ( ; is_run(); delay_fps(60) )
	{
		// todo: 逻辑更新
		// 当前位置 + 速度
        for(i=0;i<7;i++)
        {
            x[i]-=dx;
            if (x[i]<=0)
            {
                x[i] = random(100)+640;
                score += 10;
            }
        }
        //分数高了就加速
        if ((score % 100 == 90)&&(scoreCopy!=score))
        {
            dx+=2;
            scoreCopy = score;
        }

        //让速度在200-500 循环
        if (dx>=500)
        {
            dx=200;
        }


        //判断碰撞

        if( upDown==0 )//up
        {
            for(i=0;i<7;i+=2)//偶数个在上方
            {
                if((x[i]>MAN)&&(x[i]<MAN + 20))
                    death += 1;
            }
        }
        if( upDown == 1)//down
        {
            for(i=1;i<7;i+=2)//偶数个在上方
            {
                if((x[i]>MAN)&&(x[i]<MAN + 20))
                    death += 1;
            }
        }


        //如果有上下键被按下，那就改变上下的状态
        if ( kbmsg() ) k = getkey();
        if (k.key == key_up)
        {
            upDown = 0;
        }
        else if (k.key == key_down)
        {
            upDown = 1;
        }

		// todo: 图形更新
		cleardevice();
		setcolor(GREEN);
		setfillcolor(BLUE);
		bar(0,240,640,250);//画地面
		//画障碍物
		for(i=0;i<7;i+=2)//偶数个在上方
        {
            bar(x[i],230,x[i]+20,240);
        }
		for(i=1;i<7;i+=2)//奇数个在下方
        {
            bar(x[i],250,x[i]+20,260);
        }

		//画人物方块

		if (upDown == 0)
        {
            bar(MAN,FLOOR - FLOORHEIGHT - 10,MAN + 10, FLOOR - FLOORHEIGHT);
            //printf("画了人物。坐标：左：%d 上：%d 右：%d 下：%d \n",MAN,FLOOR+FLOORHEIGHT+10,MAN+10,FLOOR + FLOORHEIGHT);
        }
        else if (upDown == 1)
		{
		    bar(MAN,FLOOR,MAN + 10, FLOOR + 10);
		    //printf("画了人物。坐标：左：%d 上：%d 右：%d 下：%d \n",MAN,FLOOR,MAN+10,FLOOR-10);
		}

		{// 画帧率文字
			char str[20];
			sprintf(str, "fps %.02f", getfps()); //调用getfps取得当前帧率
			setcolor(WHITE);
			outtextxy(0, 0, str);
		}
		{// 画测试文字
			char str[20];
			sprintf(str, "你死了%d次,分数：%d,速度：%d .", death,score-death,dx); //调用getfps取得当前帧率
			setcolor(WHITE);
			outtextxy(200, 200, str);
		}
	}
}

int main(void)
{
	setinitmode(INIT_ANIMATION);
	// 图形初始化，窗口尺寸640x480
	initgraph(LENTH, HEIGHT);//横竖
	// 随机数初始化，如果需要使用随机数的话
	init();
	randomize();
	// 程序主循环
	mainloop();
	// 关闭绘图设备
	closegraph();
	return 0;
}
