clear all ; close all;
%% question1
% 1)	将图片的阴暗反转（即得到原图的负片图像）
I1 = imread('breast.tif');  %读取图像
figure(1);imshow(I1); title('Original Image') %显示原图像
I1_turn = imadjust(I1,[0 1],[1 0]); %阴暗翻转
figure(2); imshow(I1_turn);title('Reversal Image') %显示翻转图像
% 2)	将0.5 到0.75之间的灰度级扩展到范围[0 1].
I1_expand = imadjust(I1,[0.5,0.75],[0,1]);  
figure(3), imshow(I1_expand);title('linear expand image')
% 3)	使用gamma=2来增强图像
I1_improve = imadjust(I1,[0.5,0.75],[0,1],2);
figure(4); imshow(I1_improve); title('nonlinear expand image')

%% question 2
% 2.	对一个取值范围为0至1.5*106的傅里叶频谱（spectrum.tif）进行对数变换
I2=imread('spectrum.tif');
r1=log(1+double(I2));        %对数变换
r2=mat2gray(r1);
r=im2uint8(r2);
figure,imshow(I2)
figure,imshow(r)

%% question 3 3.	对花粉图像（pollen.tif）进行如下操作
I3=imread('pollen.tif');
r=histeq(I3,256);                                 %直方图均衡
figure,subplot(2,2,1),imshow(I3),title('原图')
subplot(2,2,2),imshow(r),title('均衡后图')
subplot(2,2,3),imhist(I3),title('原图直方图')
subplot(2,2,4),imhist(r),title('均衡后直方图')

%% question4 4.	学会使用函数medfilt2进行中值滤波
I4  = imread('board.tif');
fn = imnoise(I4,'salt & pepper',0.2);                %对读入图片加椒盐噪声
figure,imshow(fn);title('被椒盐噪声污染的图像');   
gm=medfilt2(fn);                                    %对噪声图片中值滤波
figure,imshow(gm);title('中值滤波后的图片');
gms=medfilt2(fn,'symmetric');
