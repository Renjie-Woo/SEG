clear;clc;
I=imread('/Users/apple/Desktop/icons/313x.png');
%change RGB to gray PNG
I=rgb2gray(I);
% gray transform

%imadjust(I,[low_in; high_in],[low_out; high_out],gamma)
%J=imadjust(I,[0.1 0.9],[0 1],1);

% Sobel
%ruturn 0/1 weights pic
BW = edge(I,'sobel');
%sobelBW = im2uint8(BW)+J;
figure;
%imshow(BW1);
subplot(1,2,1);
imshow(I);
title('original image');
subplot(1,2,2);
%imshow(sobelBW);
%title('Sobel augmented image');

%figure;
imshow(BW); 
title('sobel edge detect'); 
