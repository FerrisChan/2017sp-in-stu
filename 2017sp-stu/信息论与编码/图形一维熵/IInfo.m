

function e=IInfo(Pxy)

% ����Ϣ ,Pxy ���Ϸֲ��ܶȺ���,��ά����

if (length(find(Pxy <=0))~=0)

      error('negative probability')

end

if (abs(sum(Pxy)-1)>10e-10)

      error('sum of probability does not equal 1')

end

 

x=sum(Pxy,2);

y=sum(Pxy,1);

H=log2(Pxy)-log2(x*y)

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%