
function e=JEntropy(Pxy)

%������,xy ���Ϸֲ��ܶȺ���,��ά����
% 
% if (length(find(Pxy <=0))~=0)
% 
%       error('negative probability')
% 
% end
% 
% if (abs(sum(Pxy)-1)>10e-10)
% 
%       error('sum of probability does not equal 1')
% 
% end

H=-sum(sum(Pxy.*log2(Pxy)))
