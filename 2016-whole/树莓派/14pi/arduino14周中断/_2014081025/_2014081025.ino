				
int pbIn = 2;                  // 定义中断引脚为2，也就是D21引脚
int ledOut = A0;                // 定义改变引脚
volatile int state = LOW;      // 定义默认输入状态
 
void stateChange()
{
  state = !state;
  digitalWrite(ledOut, state);  
}    //按下开关，A0的状态就会立刻变化
void setup()
{                
  // 置ledOut引脚为输出状态
  pinMode(ledOut, OUTPUT);
 
  // 监视中断输入引脚的变化
  attachInterrupt(pbIn, stateChange, CHANGE);
}
 
void loop()                     
{
  // 模拟长时间运行的进程或复杂的任务。
  for (int i = 0; i < 100; i++)
  {
    // 什么都不做，等待10毫秒
    delay(10); 
  }
}


