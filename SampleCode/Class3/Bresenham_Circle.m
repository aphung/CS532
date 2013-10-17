%% Bresenham Circle Algorithm
figure; hold on 

x_center=10; y_center=20; radius=100;

x=0;
y=radius;
p=3-2*radius;

while x < y
    Circle(x_center,y_center,x,y); % Plot Circle
    if p<0
        p=p+4*x+6;
    else
        p=p+4*(x-y)+10;
        y=y-1;
    end
    x=x+1;
end
if x==y
    Circle(x_center,y_center,x,y); % Plot Circle
end

axis equal


