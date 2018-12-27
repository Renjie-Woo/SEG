%find the path of the file
clear all;
pt = '/Users/apple/Desktop/RHD/color/';
pto = '/Users/apple/Desktop/RHD/I/';
%the extra name ".png"
ext = '*.png';
%patch the whole name of pictures
dis = dir([pt ext]);
nms = {dis.name};
 
%decode
for k = 1:1:length(nms)
    nm = [pt nms{k}];
    X = imread(nm);
    
    image_size=size(X);
    
    dimension=numel(image_size);
    if dimension == 3
        L=rgb2gray(X);
        nm
    end
    if dimension == 2
        L = X;
    end
    show = [pto nms{k}];
    %imshow(L)
    imwrite(L,show)
end
