% used for edge detect by 'canny'

clear;clc;
%find the path of the file
pt = '/Users/apple/Desktop/Tmp/';
pto = '/Users/apple/Desktop/2Tmp/';
%the extra name ".png"
ext = '*.png';
%patch the whole name of pictures
dis = dir([pt ext]);
nms = {dis.name};
 
%decode
for k = 1:1:length(nms)
    nm = [pt nms{k}];
    
    I=imread(nm);
    
    % Canny
    %ruturn 0/1 weights pic
    BW = edge(I,'canny');
    %sobelBW = im2uint8(BW)+J;
    
    figure;
    subplot(1,2,1);
    imshow(I);
    title('original image');
    subplot(1,2,2);
    imshow(BW); 
    title('canny edge detect'); 
    
    show = [pto nms{k}];
    imwrite(BW,show)
end