%% Bresenham Line Algorithm (basic) works for 0 < k < 1
% figure; hold on 
c='bo';
h1=0; v1=0; h2=100; v2=-200; % Line1
% h1=50; v1=-20; h2=80; v2=-40; % Line2
% h1=30; v1=-60; h2=60; v2=-40; % Line3
% h1=10; v1=-70; h2=85; v2=10; % Line4
Dx=(h2-h1); Dy=(v2-v1); 
Slope=abs(Dy/Dx);% Slope
InvSlope=abs(Dx/Dy);% Inv Slope
Error=0;
%========================================
if Slope>=1
    if (h1<=h2)
        hStep = 1;
    else
        hStep = -1;
    end
    h=h1;
    if (v1 <= v2)
       for v=v1:v2
           plot(h,v,c);
           Error=Error+InvSlope;
           if Error>=0.5
               h=h+hStep; Error=Error-1;
           end
       end
    else
        for v=v1:-1:v2
            plot(h,v,c);
            Error=Error+InvSlope;
            if Error>=0.5
                h=h+hStep; Error=Error-1;
            end
        end
    end
else
    if (v1<=v2)
        vStep = 1;
    else
        vStep = -1;
    end
    v=v1;
    if (h1 <= h2)
       for h=h1:h2
           plot(h,v,c);
           Error=Error+Slope;
           if Error>=0.5
               v=v+vStep; Error=Error-1;
           end
       end
    else
        for h=h1:-1:h2
            plot(h,v,c);
            Error=Error+Slope;
            if Error>=0.5
                v=v+hStep; Error=Error-1;
            end
        end
    end
end


















