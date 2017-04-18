%% bsc 简单判断

function ret=bsc_jugde(Int)
ret = 0;
 if abs(sum(sum(Int)) -2) <= 0.00001 
     %保证行和列的和都为1
     if Int(1) == Int(4) && Int(2) == Int(3)
     % 行和列都含有相同的元素，在2×2矩阵中，只要对角线相等即可
     % 对称则返回一
         ret = 1;
     end
 else ret =0;
 end