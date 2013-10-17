%% Serpinski Triangle

N=1e4;
x_old=0; y_old=0;
figure; hold on;
for a=2:N
    c=randi([0 2]);
    
    switch c
        case 0
            x=0.5*x_old;
            y=0.5*y_old;
        case 1
            x=0.5*x_old+.25;
            y=0.5*y_old+sqrt(3)/4;
        case 2
            x=0.5*x_old+.5;
            y=0.5*y_old;
    end
    plot(x,y,'.')
    x_old=x; y_old=y;
end


title('Sierpinski’s triangle')
legend(sprintf('N=%d Iterations',N))















