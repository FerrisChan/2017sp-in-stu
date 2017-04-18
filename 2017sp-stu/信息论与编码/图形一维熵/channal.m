clear all ; close all
%% 验证1234 题
Input = [1/4,1/18,0; 1/18,1/3,1/18; 0,1/18,7/36];
% H1 = Entropy(Input)
% H2 = JEntropy(P);
% H3 = IInfo(P);

%% 求图像一维熵
% 输入图像和显示原图像和灰度图像
filename =( 'test.jpg');
image1 = imread(filename); 
im = rgb2gray(image1);
subplot(2,1,1);
imshow(image1);title('原图像')
subplot(2,1,2);
imshow(im); title('灰度图像')
[M,N]=size(im);  
temp=zeros(1,256);  
   
%对图像的灰度值在[0,255]上做统计  
for m=1:M; 
    % 一共256个可能性
    for  n=1:N;  
        if im(m,n)==0;  
            i=1;  
        else  
            i=im(m,n);  
        end  
        temp(i)=temp(i)+1;  
    end  
end  
temp=temp./(M*N);  % 每个灰度阶象素概率
   
%由熵的定义做计算  
result=0;  
   
for  i=1:length(temp)
    % 计算一位灰度熵，H = Pi*logPi, i= 1:256
    if temp(i)==0;  
        result=result;  
    else  
        result=result-temp(i)*log2(temp(i))
    end  
end  