%% Intensity Threshold of an Image
function ImOut = ThresholdIm(Im,Th,flag)
ImOut=zeros(size(Im));
if flag
    ImOut(Im>=Th)=Im(Im>=Th); % Assign intensity
else
    ImOut(Im>=Th)=1; % Assign Binary 
end





