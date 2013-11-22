
%% Convolution 
a=RData'; % Dataset
b=(ones(1,30)/30)'; % Kernel

m=size(a,1); n=size(b,1); 
for k=1:(m+n-1)
    j = max(1,k+1-n):min(k,m);
    jj = k-j+1; % Conv
%     jj = n-jj+1; % Corr
    aa = a(j); bb=b(jj);
%     C(k) = mean(aa(:).*bb(:));
    C(k) = sum(aa(:).*bb(:));
end
isequal(C,conv(a,b)')
% [C;conv(a,b)']



%% Detrend Data
RData=AD077; % Select Dataset 
Tend = 1.9e4; % Dataset Length 
t = [0:Tend]/1e3; t(end)=[]; % time vector
MData = conv(RData,ones(1,30)/30,'same'); % Find Mean (30 pixels Running Average) using convolution
RData = RData-MData; % Subtract mean to de-trend dataset
RData(1,1:20) = RData(1,20); % Left Edge
RData(1,Tend-20:Tend) = RData(1,Tend-20); % Right Edge
figure; subplot(3,1,1); plot(t,RData); xlabel('time (s)'); ylabel('Spikes')
title('De-trended Spiking Data')

% Digitize data
% zz=find(RData<-34); % AD016
zz=find(RData<-70); % AD077
DData=zeros(size(RData));
DData(zz)=1; 
subplot(3,1,2); plot(t,DData); xlabel('time (s)'); ylabel('Digitized Spikes')
sound(DData);

% Find Frequency by Convolution
Freq = conv(DData,ones(1,1e3),'same'); % Find Frequency (1s=1000 bins)
subplot(3,1,3); plot(t,Freq); xlabel('time (s)'); ylabel('Frequency (Hz)')



%% Power Spectrum
% t = 0:0.001:2; X = chirp(t,100,1,200,'q'); % Wave form
% figure; plot(X); sound(X);
t = 0:0.001:4; Y = chirp(t,100,1,200,'quadratic',[],'convex');  % Wave form
figure; subplot(2,1,1); plot(t,Y); xlabel('Time'); ylabel('Amplitude'); 
subplot(2,1,2); spectrogram(Y,128,120,128,1E3,'yaxis') 
sound(Y);

Fs=1000; % Sampling frequency
L = size(Y,2); % Length of signal
NFFT = 2^nextpow2(L); % Next power of 2 from length of y
y = fft(Y,NFFT)/L;
f = Fs/2*linspace(0,1,NFFT/2+1);
plot(f,2*abs(Y(1:NFFT/2+1)))
xlabel('Frequency (Hz)')
ylabel('|Amplitude(f)|')


