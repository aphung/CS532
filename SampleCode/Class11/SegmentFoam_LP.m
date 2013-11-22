%% Counting Touching Objects by Watershed Segmentation
clear all; close all; clc

Im=imread('Foam.jpg'); % Load image
Im=rgb2gray(Im); % Turn image from RGB to Grayscale
figure(1); imshow(Im,[]) % Display image
figure(2); imhist(Im) % Intensity threshold

%% 1) Adjust Intensity Threshold
Th=1; % Intensity Threshold (keep intensities equal and above Th)
ImTh = ThresholdIm(Im,Th,2); % Thresholded (binary) image 
figure(3); imshow(ImTh,[]) % Display Thresholded image 

%% 
ImD = bwdist(~ImTh); % Compute the distance transform of the complement of the binary image.
figure(4); imshow(ImD,[])

ImD = -ImD; % Complement the distance transform
ImD(~ImTh) = -Inf; % Force pixels that don't belong to the objects to be at -Inf.

ImW = watershed(ImD); % Implement Wateshed algorithm
figure(5); imshow(ImW) % Display 

NS = max(ImW(:))-1; % Number of Spheres
figure(1); title(['Total Number of Spheres = ',num2str(NS)])
R=zeros(NS,1); % Keeps radii of each sphere
Ct=zeros(NS,2); % Keeps centers of each sphere
for ff=2:NS+1 % Loop over all the watershed regions
    ImO=zeros(size(Im));
    zz=find(ImW==ff); ImO(zz)=1; % Isolate each region
    STATS = regionprops(ImO,'EquivDiameter','Centroid'); % Get region properties
    x=STATS.Centroid(1); y=STATS.Centroid(2); % Center of region
    r=STATS.EquivDiameter; % Radius of region
    figure(1); rectangle('Position',[x-r/2,y-r/2,r,r],'Curvature',[1,1],'EdgeColor','r')
    Ct(ff-1,1)=x; Ct(ff-1,2)=y; % Keeps centers of each sphere 
    R(ff-1)=r; % Keeps radii of each sphere 
end

figure(6); hist(R,[1:0.5:60]); % Display radius histogram
xlabel('Size (pixels)'); ylabel('Number of spheres'); 
title('Size Distribution')

%% 2) Add code to count and plot the 20 to 30 pixels large spheres. Use Matlab’s function find().
% Find Sphere of certain size (in pixels)
Size1=20; Size2=30; 

% Add code here
zz= ; % Find Spheres of certain radii Use Matlab’s function find().
for f=1:size(zz,1)
    
    
    
end
figure(1); title(['Total Number of Spheres = ',num2str(NS),'; N=',num2str(size(zz,1))])



