#include<stdio.h> 
#include<stdlib.h>
#include <graphics.h>
#include <conio.h>
#include <dos.h>

void swap(int *a, int *b) 
{ 
	int temp = *a; 
	*a = *b; 
	*b = temp; 
} 

void disp(int num, char arr[],int c){
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

int main() 
{ 
	int n, temp,i,j;
	int val;
	
	printf("Enter number of Process: "); 
	scanf("%d",&n); 
	int at[n],bt[n],ct[n],wt[n],tat[n],p[n],st[n+1];
	
	for(i=0;i<n;i++)
    {
        printf("Enter the process number   : ");
        scanf("%d",&p[i]);
        printf("Enter the arival time of the above process  : ");
        scanf("%d",&at[i]);
        printf("Enter the burst time of the above process  : ");
        scanf("%d",&bt[i]);
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
            if (at[j] >at[j+1])
            {
                swap(&p[j], &p[j+1]);
                swap(&at[j], &at[j+1]);
                swap(&bt[j], &bt[j+1]);
            }
        }  
	}
	
	st[0]= at[0]; 
	ct[0] = at[0] + bt[0]; 
	tat[0] = (ct[0]-at[0]);
    wt[0] = (tat[0]-bt[0]);
    float aw = wt[0];
	
	for(i=1; i<n; i++) 
	{ 
		temp = ct[i-1]; 
		int low = bt[i]; 
		for(j=i; j<n; j++) 
		{ 
			if(temp >= at[j] && low >= bt[j]) 
			{ 
				low = bt[j]; 
				val = j;
			} 
		} 
		ct[val] = temp + bt[val];
		tat[val] = (ct[val]-at[val]);
    	wt[val] = (tat[val]-bt[val]);
    	aw = aw + wt[val];
    	
		swap(&p[val], &p[i]);
        swap(&at[val], &at[i]);
        swap(&bt[val], &bt[i]);
        swap(&ct[val], &ct[i]);
        swap(&tat[val], &tat[i]);
        swap(&wt[val], &wt[i]);
	}
	
	aw = aw/n;
    printf("processed data \n");
    for(i=0;i<n;i++)
    {
        printf(" %2d   %2d   %2d   %2d   %2d   %2d  \n",p[i],at[i],bt[i],ct[i],tat[i],wt[i]);
        st[i] = ct[i]-bt[i];
    }
    printf("Average waiting time = %f\n",aw);
    
    
    
    
    printf("Do You want to display the GANTT CHART \n         Enter 1 : \n");
    int choice =1,time;
    scanf("%d",&choice);
    char str[12];
	char tim[10];
    if(choice ==1)
    {
    	
		int graphicdriver=DETECT,graphicmode;
    	initgraph(&graphicdriver,&graphicmode,"c:\\turboc3\\bgi");
    	setcolor(GREEN);
		rectangle(5,30,635,450);
		settextstyle(4,HORIZ_DIR,4);
		setcolor(WHITE);
		outtextxy(150,0," GANTT CHART");
		settextstyle(9,HORIZ_DIR,1);
		outtextxy(210,30,"For SJF Algorithm ");
		setlinestyle(SOLID_LINE,0,2);
    	float fract = 620/ct[n-1];
    	int lx,ly,ry;
    	float rx;
    	lx = 20;
    	ly = 200;
    	ry = 300;
    	for(i=0;i<n;i++)
    	{
    		disp(p[i],str,1);
    		int num = i%5;
    		rx = fract*ct[i];
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
       		bar(lx,ly,rx,ry);
			outtextxy((lx+5),305,str);
			disp(ct[i],tim,0);
			outtextxy((rx-5),185,tim);
			lx = fract*st[i+1];	
		}
		outtextxy(50,400,"BLACK PLACES INDICATES CPU IDLE TIME");
		disp(st[0],str,0);
		outtextxy(15,185,str);
		getch();
	}
} 

