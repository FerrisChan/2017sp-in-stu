clear all ; close all;
%% question1
% 1)	��ͼƬ��������ת�����õ�ԭͼ�ĸ�Ƭͼ��
I1 = imread('breast.tif');  %��ȡͼ��
figure(1);imshow(I1); title('Original Image') %��ʾԭͼ��
I1_turn = imadjust(I1,[0 1],[1 0]); %������ת
figure(2); imshow(I1_turn);title('Reversal Image') %��ʾ��תͼ��
% 2)	��0.5 ��0.75֮��ĻҶȼ���չ����Χ[0 1].
I1_expand = imadjust(I1,[0.5,0.75],[0,1]);  
figure(3), imshow(I1_expand);title('linear expand image')
% 3)	ʹ��gamma=2����ǿͼ��
I1_improve = imadjust(I1,[0.5,0.75],[0,1],2);
figure(4); imshow(I1_improve); title('nonlinear expand image')

%% question 2
% 2.	��һ��ȡֵ��ΧΪ0��1.5*106�ĸ���ҶƵ�ף�spectrum.tif�����ж����任
I2=imread('spectrum.tif');
r1=log(1+double(I2));        %�����任
r2=mat2gray(r1);
r=im2uint8(r2);
figure,imshow(I2)
figure,imshow(r)

%% question 3 3.	�Ի���ͼ��pollen.tif���������²���
I3=imread('pollen.tif');
r=histeq(I3,256);                                 %ֱ��ͼ����
figure,subplot(2,2,1),imshow(I3),title('ԭͼ')
subplot(2,2,2),imshow(r),title('�����ͼ')
subplot(2,2,3),imhist(I3),title('ԭͼֱ��ͼ')
subplot(2,2,4),imhist(r),title('�����ֱ��ͼ')

%% question4 4.	ѧ��ʹ�ú���medfilt2������ֵ�˲�
I4  = imread('board.tif');
fn = imnoise(I4,'salt & pepper',0.2);                %�Զ���ͼƬ�ӽ�������
figure,imshow(fn);title('������������Ⱦ��ͼ��');   
gm=medfilt2(fn);                                    %������ͼƬ��ֵ�˲�
figure,imshow(gm);title('��ֵ�˲����ͼƬ');
gms=medfilt2(fn,'symmetric');
