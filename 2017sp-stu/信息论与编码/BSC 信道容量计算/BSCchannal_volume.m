%% 二元对称信道BSC的计算容量方法
   % 2014081025 14通信 陈李锋
close all; clear all;
%% 判断是否为对称信道

Int = [1/4,3/4;3/4,1/4]; % 输入矩阵
ret = 0;
 if abs(sum(sum(Int)) -2) <= 0.00001 
     %保证行和列的和都为1
     if Int(1) == Int(4) && Int(2) == Int(3)
     % 行和列都含有相同的元素，在2×2矩阵中，只要对角线相等即可
     % 对称则返回1
         ret = 1;
     end
 else ret =0;
 end
if ret == 1
    disp('输入的信道矩阵为对称的 ')
else
    disp('输入的信道矩阵不为对称的')
end

%% 计算信道容量
if ret == 1
    C = log2(2) + Int(1)*log2(Int(1)) + Int(2)*log2(Int(2));
end

%% 绘制当w, p 从0到1之间变化的信道容量曲线
[w,p] = meshgrid(0:0.001:1);
C2 = -(w.*(1-p)+(1-w).*p).*log2(w.*(1-p)+(1-w).*p)-(w.*p+(1-w).*(1-p)).*log2(w.*p+(1-w).*(1-p))+(p.*log2(p)+(1-p).*log2(1-p));
meshz(p,w,C2)
title('信道容量曲线'),xlabel('p'),zlabel('信道容量'),ylabel('w')

