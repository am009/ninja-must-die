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
	//x,y��¼��ǰλ�ã�dx,dy��¼�ٶ�������r��¼Բ�뾶
	int x[7];
	int dx = 200;
	int upDown = 0;//0���ϣ�1���¡�
	key_msg k = {0};
    int i, j;//forѭ���õ�
    int death = 0 ;//�����Ĵ���
    int score = 0 ;
    int scoreCopy = -2;
    //ע��ȥ��ʼ��һ�³�ʼλ�á�
    x[0] = 620;
    x[1] = 500;
    //x[2] = 690;
    //x[4] = 800;


	for ( ; is_run(); delay_fps(60) )
	{
		// todo: �߼�����
		// ��ǰλ�� + �ٶ�
        for(i=0;i<7;i++)
        {
            x[i]-=dx;
            if (x[i]<=0)
            {
                x[i] = random(100)+640;
                score += 10;
            }
        }
        //�������˾ͼ���
        if ((score % 100 == 90)&&(scoreCopy!=score))
        {
            dx+=2;
            scoreCopy = score;
        }

        //���ٶ���200-500 ѭ��
        if (dx>=500)
        {
            dx=200;
        }


        //�ж���ײ

        if( upDown==0 )//up
        {
            for(i=0;i<7;i+=2)//ż�������Ϸ�
            {
                if((x[i]>MAN)&&(x[i]<MAN + 20))
                    death += 1;
            }
        }
        if( upDown == 1)//down
        {
            for(i=1;i<7;i+=2)//ż�������Ϸ�
            {
                if((x[i]>MAN)&&(x[i]<MAN + 20))
                    death += 1;
            }
        }


        //��������¼������£��Ǿ͸ı����µ�״̬
        if ( kbmsg() ) k = getkey();
        if (k.key == key_up)
        {
            upDown = 0;
        }
        else if (k.key == key_down)
        {
            upDown = 1;
        }

		// todo: ͼ�θ���
		cleardevice();
		setcolor(GREEN);
		setfillcolor(BLUE);
		bar(0,240,640,250);//������
		//���ϰ���
		for(i=0;i<7;i+=2)//ż�������Ϸ�
        {
            bar(x[i],230,x[i]+20,240);
        }
		for(i=1;i<7;i+=2)//���������·�
        {
            bar(x[i],250,x[i]+20,260);
        }

		//�����﷽��

		if (upDown == 0)
        {
            bar(MAN,FLOOR - FLOORHEIGHT - 10,MAN + 10, FLOOR - FLOORHEIGHT);
            //printf("����������꣺��%d �ϣ�%d �ң�%d �£�%d \n",MAN,FLOOR+FLOORHEIGHT+10,MAN+10,FLOOR + FLOORHEIGHT);
        }
        else if (upDown == 1)
		{
		    bar(MAN,FLOOR,MAN + 10, FLOOR + 10);
		    //printf("����������꣺��%d �ϣ�%d �ң�%d �£�%d \n",MAN,FLOOR,MAN+10,FLOOR-10);
		}

		{// ��֡������
			char str[20];
			sprintf(str, "fps %.02f", getfps()); //����getfpsȡ�õ�ǰ֡��
			setcolor(WHITE);
			outtextxy(0, 0, str);
		}
		{// ����������
			char str[20];
			sprintf(str, "������%d��,������%d,�ٶȣ�%d .", death,score-death,dx); //����getfpsȡ�õ�ǰ֡��
			setcolor(WHITE);
			outtextxy(200, 200, str);
		}
	}
}

int main(void)
{
	setinitmode(INIT_ANIMATION);
	// ͼ�γ�ʼ�������ڳߴ�640x480
	initgraph(LENTH, HEIGHT);//����
	// �������ʼ���������Ҫʹ��������Ļ�
	init();
	randomize();
	// ������ѭ��
	mainloop();
	// �رջ�ͼ�豸
	closegraph();
	return 0;
}
