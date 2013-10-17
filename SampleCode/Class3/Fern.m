%% Fern Fractal
NumOfPts = 10000;
iterations = 50;

pts = zeros(NumOfPts,2);

for j = 1:NumOfPts
	
	x = rand(1);
	y = rand(1);
	
	for i = 1:iterations
		
		p = rand(1);
				
		if p < .01
			
			xn = 0;
			yn = .16*y;
			x = xn;
			y = yn;
			
		elseif p < .08
			
			xn = .2*x-.26*y;
			yn = .23*x+.22*y+1.6;
			x = xn;
			y = yn;
			
		elseif p < .15
			
			xn = -.15*x+.28*y;
			yn = .26*x+.24*y+.44;
			x = xn;
			y = yn;
			
		else
			
			xn = .85*x+.04*y;
			yn = -.04*x+.85*y+1.6;
			x = xn;
			y = yn;
			
		end
				
	end%i
	
	pts(j,1) = x;
	pts(j,2) = y;
	

	
end%j

xs = pts(:,1);
ys = pts(:,2);

plot(xs,ys,'.','Color','g')
axis([min(xs)*1.5,max(xs)*1.5,min(ys)*1.05,max(ys)*1.05]);