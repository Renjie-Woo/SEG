%find the path of the file
pt = '/Users/apple/Desktop/png2edge_detect/I/';
%the extra name ".png"
ext = '*.png';
%patch the whole name of pictures
dis = dir([pt ext]);
nms = {dis.name};
 
%decode
for k = 1:1:length(nms)
    nm = [pt nms{k}];
    X = imread(nm);
    
    annotation = X(:, :, 1);
    annotation = bitor(annotation, bitshift(X(:, :, 2), 8));
    annotation = bitor(annotation, bitshift(X(:, :, 3), 16));
    output = annotation*256;

    %imshow(output)
    
    show = [pt 'decode_' nms{k}];
    imwrite(output,show)
end
