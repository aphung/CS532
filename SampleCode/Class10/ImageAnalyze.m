pth = 'C:\Users\aphung\Documents\GitHub\CS532\SampleCode\Class10\Cells.bmp';
Im = imread(pth);
size(Im)
max(Im(:));
Im1 = imread('C:\Users\aphung\Documents\GitHub\CS532\SampleCode\Class10\DeathValey.jpg');

figure;
imshow(Im);

figure;
imshow(Im1);

%Im(100, 30);