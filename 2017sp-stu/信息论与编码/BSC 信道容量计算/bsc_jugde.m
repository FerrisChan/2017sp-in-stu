%% bsc ���ж�

function ret=bsc_jugde(Int)
ret = 0;
 if abs(sum(sum(Int)) -2) <= 0.00001 
     %��֤�к��еĺͶ�Ϊ1
     if Int(1) == Int(4) && Int(2) == Int(3)
     % �к��ж�������ͬ��Ԫ�أ���2��2�����У�ֻҪ�Խ�����ȼ���
     % �Գ��򷵻�һ
         ret = 1;
     end
 else ret =0;
 end