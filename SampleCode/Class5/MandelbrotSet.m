%% Mandelbrot Set
clear all; clc
depth = 100; % 
n=500; % Number of Grid points
Delta=3e-3; % Grid Step

xa=-0.5; % X start point
ya=0.0; % Y start point
% xa=-0.77; % X start point
% ya=-0.25; % Y start point
% Delta=Delta/10;

Im=zeros(n,n);
xc=1; %counters
for x=xa-Delta*n/2:Delta:xa+Delta*n/2
    yc=1; 
    for y=ya-Delta*n/2:Delta:ya+Delta*n/2 
        z0 = x+y*1i;
        z = 0;  % Mandelbrot Set
        k = 0;
        while abs(z) < 2 && k < depth  % Mandelbrot Set
            z = z^2+z0; % Mandelbrot Set
            k = k + 1;
        end     

        Im(yc,xc)=k;
        yc=yc+1;
    end
    xc=xc+1;
end

figure; image(Im)% axis image
% set(gca,'XTick',[1,333,666,1000])
% set(gca,'XTickLabel',{'-2','-1','0','1'})
% set(gca,'YTick',[1,333,666,1000])
% set(gca,'YTickLabel',{'-1.5','-0.5','0.5','1.5'})
