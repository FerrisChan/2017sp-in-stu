clear all ; close all
%% ��֤1234 ��
Input = [1/4,1/18,0; 1/18,1/3,1/18; 0,1/18,7/36];
% H1 = Entropy(Input)
% H2 = JEntropy(P);
% H3 = IInfo(P);

%% ��ͼ��һά��
% ����ͼ�����ʾԭͼ��ͻҶ�ͼ��
filename =( 'test.jpg');
image1 = imread(filename); 
im = rgb2gray(image1);
subplot(2,1,1);
imshow(image1);title('ԭͼ��')
subplot(2,1,2);
imshow(im); title('�Ҷ�ͼ��')
[M,N]=size(im);  
temp=zeros(1,256);  
   
%��ͼ��ĻҶ�ֵ��[0,255]����ͳ��  
for m=1:M; 
    % һ��256��������
    for  n=1:N;  
        if im(m,n)==0;  
            i=1;  
        else  
            i=im(m,n);  
        end  
        temp(i)=temp(i)+1;  
    end  
end  
temp=temp./(M*N);  % ÿ���ҶȽ����ظ���
   
%���صĶ���������  
result=0;  
   
for  i=1:length(temp)
    % ����һλ�Ҷ��أ�H = Pi*logPi, i= 1:256
    if temp(i)==0;  
        result=result;  
    else  
        result=result-temp(i)*log2(temp(i))
    end  
end  