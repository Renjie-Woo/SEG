% 将灰度图像转换为RGB格式

%find the path of the file
clear all;
pt = '/Users/apple/Desktop/dicom2png/20180815/';
pto = '/Users/apple/Desktop/predict/';
%the extra name ".png"
ext = '*.png';
%patch the whole name of pictures
dis = dir([pt ext]);
nms = {dis.name};
 %
%decode
for k = 1:1:length(nms)
    nm = [pt nms{k}];
    X = imread(nm);
    
    [rows,cols]=size(X);
    r=zeros(rows,cols);
    g=zeros(rows,cols);
    b=zeros(rows,cols);
    r=double(X);
    g=double(X);
    b=double(X);
    rgb=cat(3,r,g,b);

    show = [pto '20180815_' nms{k}];

    imwrite(uint8(rgb),show)
    %imwrite(uint8(X),show)
end