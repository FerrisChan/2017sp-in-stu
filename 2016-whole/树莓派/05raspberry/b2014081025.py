## 这个程序循环实现简单的冒泡排序
## author：陈李锋
## data: 2016,10,10

def bubble(l):    
    flag = True
    for i in range(len(l)-1, 0, -1):  
        if flag: 
            flag = False
            for j in range(i):
                if l[j] > l[j + 1]:
                    l[j], l[j+1] = l[j+1], l[j]
                    flag = True
        else:
            break
    print (l)

lis=list(input())  #输入一个数列
bubble(lis)        #调用冒泡函数
 
