
%% Square Wave
SQx=[0 0 0.5 0.5 0.5  1.0  1.0  1.0];
SQy=[0 1 1.0 0.0 -1.0 -1.0 0.0 1.0 ];
figure; hold on; line(SQx,SQy)

f=1; % Frequency (Hz) 
t=0:0.01:2; % Time 
b=[1:2:121]; % Sin Coefficients
FSin=0;
for n=1:size(b,2)
    FSin=FSin+1/b(n)*sin(b(n)*2*pi*t);
end
FS = 4/pi*FSin; 
plot(t,FS,'r')
xlim([-0.1 2.1]); ylim([-1.1 1.1]);

%% Fourier Series
a=[1 1 1 1 1]; % Cos Coefficients
b=0.5*[1 1 1 1 1]; % Sin Coefficients
f=1; % Frequency (Hz) # of oscilations in 1 second
t=0:0.01:10; % Time 
FCos=0; FSin=0;
for n=1:size(a,2)
    FCos=FCos+a(n)*cos(n*2*pi*t);
    FSin=FSin+b(n)*sin(n*2*pi*t);
end
FS = 1/2 + FCos + FSin; 
plot(t,FS)

%%
