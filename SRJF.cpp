#include<stdio.h> 
#include<stdlib.h>
#include <graphics.h>
#include <conio.h>
#include <dos.h>

int graphicdriver=DETECT,graphicmode;

void swap(int *a, int *b) 
{ 
	int temp = *a; 
	*a = *b; 
	*b = temp; 
} 

void disp(int num, char arr[],int c)
{
	int digi = 0;
	int n = num;
	while(n>0){
		digi++;
		n/=10;
	}
	digi = digi==0 ? 1 : digi;
	if(c == 1){	
			digi+=2;
			arr[digi--] = '\0';
			while(digi >=2){
			arr[digi--] = num%10 + '0';
			num/=10;	
			}
			arr[digi--] = '-';
			arr[digi--] = 'P';
	}
	else{
		arr[digi--] = '\0';
		while(digi >=0){
		arr[digi--] = num%10 + '0';
		num/=10;	
		}
	}
}

void graph(int p)
{
	int num = p%5;
	switch (num) 
	{
        case 0:
            setfillstyle(LINE_FILL,BLUE);
            break;
        case 1:
            setfillstyle(XHATCH_FILL,RED);
            break;
        case 2:
            setfillstyle(WIDE_DOT_FILL,YELLOW);
            break;
        case 3:
            setfillstyle(INTERLEAVE_FILL,MAGENTA);
            break;
        case 4:
        	setfillstyle(HATCH_FILL,BROWN);
            break;
	}
}

int main() 
{ 
	int lx,rx;
	int n,i,j;
	int val,run =0;
	char str[12];
	char tim[10];
	
	printf("Enter number of Process: "); 
	scanf("%d",&n); 
	int at[n],bt[n],ct[n+1],wt[n],tat[n],p[n],st[n+1],gc[n];
	
	for(i=0;i<n;i++)
    {
        printf("Enter the process number   : ");
        scanf("%d",&p[i]);
        printf("Enter the arival time of the above process  : ");
        scanf("%d",&at[i]);
        printf("Enter the burst time of the above process  : ");
        scanf("%d",&bt[i]);
        gc[i] = bt[i];
        run+=bt[i];
    }
	printf("Given Data\n");
    for(i=0;i<n;i++)
    {
        printf(" %d   %d   %d  \n",p[i],at[i],bt[i]);
    }
        
    for (i = 0; i < n-1; i++)
    {
        for (j = 0; j < n-i-1; j++)
        {
            if (p[j] >p[j+1])
            {
                swap(&p[j], &p[j+1]);
                swap(&at[j], &at[j+1]);
                swap(&bt[j], &bt[j+1]);
            }
        }  
    }
    
    for (i = 0; i < n-1; i++)
    {
        for (j = 0; j < n-i-1; j++)
        {
            if (bt[j] >bt[j+1])
            {
                swap(&p[j], &p[j+1]);
                swap(&at[j], &at[j+1]);
                swap(&bt[j], &bt[j+1]);
            }
        }  
    }
    
    for (i = 0; i < n-1; i++)
    {
        for (j = 0; j < n-i-1; j++)
        {
            if (at[j] >at[j+1])
            {
                swap(&p[j], &p[j+1]);
                swap(&at[j], &at[j+1]);
                swap(&bt[j], &bt[j+1]);
            }
        }  
	}

	initgraph(&graphicdriver,&graphicmode,"c:\\turboc3\\bgi");
    setcolor(GREEN);
	rectangle(5,30,635,450);
	settextstyle(4,HORIZ_DIR,4);
	setcolor(WHITE);
	outtextxy(150,0," GANTT CHART");
	settextstyle(9,HORIZ_DIR,1);
	outtextxy(210,30,"For SRTF Algorithm ");
	setlinestyle(SOLID_LINE,0,2);
	float aw;
	int time = 1;
	time  = at[0];
	int fract =  500/run;
	lx =20;
	rx = 20;
	int temp = 1;
    while(run > 0)
    {
    	int ind = 0;
		rx = rx +fract;
    	val = 100;
        ind = n;
        for (j = 0 ; j < n; j++)
        {
        	if (bt[j] < val && bt[j]>0 && at[j] <= time)
        	{
				ind = j;
                val = bt[j];  
            }
    	}
    	
    	if(temp!=ind)
    	{
    		disp((ind+1),str,1);
			outtextxy(lx,305,str);
			disp(time,tim,0);
			outtextxy((rx-fract),185,tim);
			temp  = ind;
		}
    	
        time = time+1;
        printf(" process taken is %d  ---------- %d\n",(ind+1),time);
    	bt[ind] = bt[ind] - 1;	
		if(ind!=n)
		{
			graph(ind);
			run-=1;	
			rx = 20+fract*time;		
			bar(lx,200,rx,300);
			lx = rx;
		}
		if(bt[ind]==0)
    	{
    		ct[ind] = time;
            tat[ind] = ct[ind] - at[ind];
            wt[ind] = tat[ind] - gc[ind];
        }
	}
	
	printf("processed data \n");
    for(i=0;i<n;i++)
    {
        printf(" %2d   %2d   %2d   %2d   %2d   %2d  \n",p[i],at[i],gc[i],ct[i],tat[i],wt[i]);
		aw = aw + wt[i];   
    }
    aw = aw/n;
    printf("Awerage Waiting Time is =  %f",aw);
    disp(time,tim,0);
	outtextxy((rx-fract),185,tim);
    getch();
}
