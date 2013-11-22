% 2D Convolution 
Im=imread('ZEBRAS.JPG'); % Load Image
Im=double(rgb2gray(Im)); % Make it smaller
[M,N]=size(Im); % Get the horizontal and vertical size of the Image

k=[-1 0 1; -1 0 1; -1 0 1]; % Kernel Matrix (used for Matlab convolution)
kv=[1 1 1]'; kh=[-1 0 1]; % Separated Kernel Matrix into column(kv) and row(kh) vectors
% Note that the matrix multiplication gives k=kv*kh 

for f=1:N % Loop Columns 
    bb=ConvZ(Im(:,f),kv(:)); % Convolving the columns (using 1D ConvZ code)
    cc(f,:)=bb(2:end-1); % Cut out the edge efects from convolution
end
figure; imshow(cc,[])

for f=1:M % Loop Rows 
    C=ConvZ(cc(:,f),kh(:)); C=C(2:end-1); % Convolving the rows (using 1D ConvZ code)
    Out(f,:)=C; % Cut out the edge efects from convolution
end
figure; imshow(Out,[])

% Compare 
IM=conv2(Im,k,'same'); % Matlab Convolution function (to compare with)
isequal(Out,IM) % Comapre if the convolution result is same








