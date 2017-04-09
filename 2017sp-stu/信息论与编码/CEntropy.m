

function e=CEntropy(Pxy,sign)

%条件熵. Pxy =联合分布密度函数,二维矩阵, sign=‘x’表示y关于x的条件概率

if (length(find(Pxy <=0))~=0)

      error('negative probability')

end

if (abs(sum(Pxy)-1)>10e-10)

      error('sum of probability does not equal 1')

end

 

x=sum(Pxy,2);

y=sum(Pxy,1);

if sign=='x'

   H=JEntropy(xy)-Entropy(x);

elseif sign=='y'

   H=JEntropy(xy)-Entropy(y);

else H=FALSE

end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%