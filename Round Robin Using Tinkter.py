from tkinter import *
from tkinter import ttk
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import (FigureCanvasTkAgg,NavigationToolbar2Tk)

root = Tk()
root.title(" SMS - CW-2")

# Variables

at1,at2,at3,at4,at5,at6,bt1,bt2,bt3,bt4,bt5,bt6,frame,q,AAT,AWT,content = NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE

def UI():
    global content
    content = ttk.Frame(root)

    processlbl = ttk.Label(content, text="Process Data")
    l1 = ttk.Label(content, text="Arrival Time")
    l2 = ttk.Label(content, text="Burst Time")

    global at1,at2,at3,at5,at4,at6,bt1,bt2,bt3,bt5,bt4,bt6,q,AAT,AWT


    p1 = ttk.Label(content, text="1")
    p2 = ttk.Label(content, text="2")
    p3 = ttk.Label(content, text="3")
    p4 = ttk.Label(content, text="4")
    p5 = ttk.Label(content, text="5")
    p6 = ttk.Label(content, text="6")

    at1 = ttk.Entry(content, font=('calibre',10,'normal'))
    at2 = ttk.Entry(content, font=('calibre',10,'normal'))
    at3 = ttk.Entry(content, font=('calibre',10,'normal'))
    at4 = ttk.Entry(content, font=('calibre',10,'normal'))
    at5 = ttk.Entry(content, font=('calibre',10,'normal'))
    at6 = ttk.Entry(content, font=('calibre',10,'normal'))


    bt1 = ttk.Entry(content, font=('calibre',10,'normal'))
    bt2 = ttk.Entry(content, font=('calibre',10,'normal'))
    bt3 = ttk.Entry(content, font=('calibre',10,'normal'))
    bt4 = ttk.Entry(content, font=('calibre',10,'normal'))
    bt5 = ttk.Entry(content, font=('calibre',10,'normal'))
    bt6 = ttk.Entry(content, font=('calibre',10,'normal'))

    ql = ttk.Label(content, text="Time Quantam :")
    q = ttk.Entry(content, font=('calibre',10,'normal'))

    aatl = ttk.Label(content, text="Average Turnaround Time :")
    awtl = ttk.Label(content, text="Average Waiting Time :")
    

    submit = Button(content, text="            Caluculate          ", fg="Black", bg="Green", command=insert)
    
    global frame
    frame = ttk.Frame(root, borderwidth=5, relief="ridge", width=525, height=340)
    name = ttk.Label(root, relief="ridge", text="By Venkata Abhiram Edapalapati")
    


    content.grid(column=0, row=2)

    l1.grid(column=3, row=3, columnspan=2)
    l2.grid(column=5, row=3, columnspan=2)

    processlbl.grid(column = 1 , row = 0, columnspan=6)
    p1.grid(column=0, row=4, columnspan=2)
    at1.grid(column=3, row=4, columnspan=2, pady=5, padx=5)
    bt1.grid(column=5, row=4, columnspan=2, pady=5, padx=5)

    p2.grid(column=0, row=5, columnspan=2)
    at2.grid(column=3, row=5, columnspan=2, pady=5, padx=5)
    bt2.grid(column=5, row=5, columnspan=2, pady=5, padx=5)
    
    p3.grid(column=0, row=6, columnspan=2)
    at3.grid(column=3, row=6, columnspan=2, pady=5, padx=5)
    bt3.grid(column=5, row=6, columnspan=2, pady=5, padx=5)

    p4.grid(column=0, row=7, columnspan=2)
    at4.grid(column=3, row=7, columnspan=2, pady=5, padx=5)
    bt4.grid(column=5, row=7, columnspan=2, pady=5, padx=5)

    p5.grid(column=0, row=8, columnspan=2)
    at5.grid(column=3, row=8, columnspan=2, pady=5, padx=5)
    bt5.grid(column=5, row=8, columnspan=2, pady=5, padx=5)

    p6.grid(column=0, row=9, columnspan=2)
    at6.grid(column=3, row=9, columnspan=2, pady=5, padx=5)
    bt6.grid(column=5, row=9, columnspan=2, pady=5, padx=5)

    submit.grid(column= 3, row=12, columnspan=5, pady=5, padx=5)
    ql.grid(column=2, row=10, columnspan=2)
    q.grid(column=4, row=10, columnspan=2, pady=5, padx=5)

    aatl.grid(column=2, row=14, columnspan=2)
    awtl.grid(column=2, row=15, columnspan=2)
    

    frame.grid(column=1, row=0, columnspan=6, rowspan=5,  pady=5, padx=5)
    name.grid(column=1, row = 7, columnspan=6,  pady=5, padx=20)


def insert():

    global at1,at2,at3,at5,at4,at6,bt1,bt2,bt3,bt5,bt4,bt6,q

    data = [[0, 0 ,1], [0, 0, 2], [0, 0, 3],[0, 0, 4], [0, 0, 5],[0, 0, 6]]
    data[0][0]= int(at1.get())
    data[1][0]= int(at2.get())
    data[2][0]= int(at3.get())
    data[3][0]= int(at4.get())
    data[4][0]= int(at5.get())
    data[5][0]= int(at6.get())

    data[0][1]= int(bt1.get())
    data[1][1]= int(bt2.get())
    data[2][1]= int(bt3.get())
    data[3][1]= int(bt4.get())
    data[4][1]= int(bt5.get())
    data[5][1]= int(bt6.get())
    n = 6
    sorted_multi_list = sorted(data, key=lambda x: x[0])
    quantum = int(q.get()) 
    findavgTime(n, sorted_multi_list, quantum)


df = pd.DataFrame(columns = ["Task", "Start", "Finish"])

def findWaitingTime(n, bt, wt, quantum): 
    global df
    rem_bt = [0] * n
    for i in range(n): 
        rem_bt[i] = bt[i][1]
    
    print(bt, rem_bt)
    t = 0 
    while(1):
        done = True
        for i in range(n): 
            if (rem_bt[i] > 0) :
                done = False
                if (rem_bt[i] > quantum) :
                    start = t
                    print(start)
                    t += quantum 
                    rem_bt[i] -= quantum
                    df = df.append({'Task' : "Process"+str(bt[i][2]), 'Start' : start, 'Finish' : t}, ignore_index = True)
                else:
                    start = t
                    t = t + rem_bt[i] 
                    wt[i] = t - (bt[i][1] +bt[i][0])  
                    rem_bt[i] = 0
                    df = df.append({'Task' : "Process"+str(bt[i][2]), 'Start' : start, 'Finish' : t}, ignore_index = True)
        if (done == True):
            break
              
def findTurnAroundTime(n, bt, wt, tat):
    for i in range(n):
        tat[i] = bt[i][1] + wt[i] 
   
def findavgTime(n, bt, quantum): 
    global df, content,AAT, AWT
    wt = [0] * n
    tat = [0] * n 
    findWaitingTime(n, bt, wt, quantum) 
    findTurnAroundTime(n, bt, wt, tat) 
    print("Processes    Burst Time     Waiting", "Time    Turn-Around Time")
    total_wt = 0
    total_tat = 0
    for i in range(n):
        total_wt = total_wt + wt[i] 
        total_tat = total_tat + tat[i] 
        print(" ", i + 1, "\t\t", bt[i][1], "\t\t", wt[i], "\t\t", tat[i])
    print("\nAverage waiting time = %.5f "%(total_wt /n) )
    print("Average turn around time = %.5f "% (total_tat / n))

    AAT = ttk.Label(content, font=('calibre',10,'normal'),text=""+str(total_tat /n)+" Min")
    AWT = ttk.Label(content, font=('calibre',10,'normal'),text=""+str(total_wt /n)+" Min")
    AAT.grid(column=4, row=14, columnspan=2, pady=5, padx=5)
    AWT.grid(column=4, row=15, columnspan=2, pady=5, padx=5)

    df["Diff"] = df.Finish - df.Start
    print(df)
    color = {"Process1":"turquoise", "Process2":"green","Process3":"red", "Process4":"blue","Process5":"yellow","Process6":"orange"}
    fig,ax=plt.subplots(figsize=(5,3))
    labels=[]
    for i, task in enumerate(df.groupby("Task")):
        labels.append(task[0])
        data = task[1][["Start", "Diff"]]
        ax.broken_barh(data.values, (i-0.4,0.8), color=color[task[0]] )

    ax.set_yticks(range(len(labels)))
    ax.set_yticklabels(labels) 
    ax.set_xlabel("time [ms]")
    plt.tight_layout()
    global frame
    canvas = FigureCanvasTkAgg(fig,master = frame)  
    canvas.draw()
    canvas.get_tk_widget().pack()
    toolbar = NavigationToolbar2Tk(canvas,frame)
    toolbar.update()
    canvas.get_tk_widget().pack()
    df = df.iloc[0:0]

if __name__ =="__main__":
    UI()
    root.mainloop()