%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function e=Entropy(input)
% 
% if (length(find(input <  0))~=0)
% 
%       error('negative probability')
% 
% end
% 
% if (abs(sum(input)-1)>10e-10)
% 
%       error('sum of probability does not equal 1')
% 
% end

H=-sum(input.*log2(input))

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

 

function e=JEntropy(Pxy)

%������,xy ���Ϸֲ��ܶȺ���,��ά����

if (length(find(Pxy <=0))~=0)

      error('negative probability')

end

if (abs(sum(Pxy)-1)>10e-10)

      error('sum of probability does not equal 1')

end

H=-sum(sum(Pxy.*log2(Pxy)))

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

 

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