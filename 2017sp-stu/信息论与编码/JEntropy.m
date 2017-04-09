
function e=JEntropy(Pxy)

%联合熵,xy 联合分布密度函数,二维矩阵
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
