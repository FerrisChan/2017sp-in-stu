## 这个程序循环判断键盘输入的三个数据是否为三角形，若为三角形并判断其类型；若不为三角形则退出循环
## author：陈李锋
## data: 2016,10,10

while True:         
   a = int(input('输入三角形的第一条边：'))  # 输入三条边，并使数据为整形
   b = int(input('输入三角形的第二条边：'))
   c = int(input('输入三角形的第三条边：'))
   if a+b>c and b+c>a and a+c>b :           #首先判断是否为三角形
      print ('输入的三条边能组成三角形')    
      if a == b or a == c :                 #判断是否为等腰或等边三角形
         if b == c :
            print('等边三角形')
         else:
            print('等腰三角形')              
      elif a**2+b**2==c**2 or a**2+c**2==b**2 or b**2+c**2==a**2:    # 判断是否为直角三角形
            print('其为直角三角形')
      else :
         print('一般三角形')                #不为等腰或直角，则为一般三角形   
   else:
      print ('输入的三条边不能能组成三角形')    # 不为三角形，则退出循环
      False
      print('The end')
