

function e=CEntropy(Pxy,sign)

%������. Pxy =���Ϸֲ��ܶȺ���,��ά����, sign=��x����ʾy����x����������

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