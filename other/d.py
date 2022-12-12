import matplotlib.pyplot as plt

total=[]
file=open("result.txt","r")
count=0
while True:
    
    line1=file.readline()
    if not line1:
        break
    line2=file.readline()
    total.append([int(line1[:-1]),list(map(int,line2[:-1].split(" ")))])
    
file.close()

total.sort(key=lambda x:x[0])
x=[]
ba=[]
ff=[]
wf=[]
bf=[]
for i in total:
    x.append(i[0])
    ba.append(i[1][0]/pow(10,6))
    ff.append(i[1][1]/pow(10,6))
    wf.append(i[1][2]/pow(10,6))
    bf.append(i[1][3]/pow(10,6))
y=[ba,ff,wf,bf]
print(y)




approach=["buddy-allocation", "first-fit", "worst-fit","best-fit"]
for i in range(4):
    plt.plot(x, y[i], label=approach[i])

plt.legend(approach)
plt.xlabel('Number of operations')
plt.ylabel('run time (s)')
plt.title('Run Time Analysis')
plt.show()