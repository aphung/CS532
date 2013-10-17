%%
function Circle(x_center,y_center,x,y)
plot(x_center+x,y_center+y,'ro')
plot(x_center-x,y_center+y,'ro')
plot(x_center+x,y_center-y,'ro')
plot(x_center-x,y_center-y,'ro')
plot(x_center+y,y_center+x,'ro')
plot(x_center-y,y_center+x,'ro')
plot(x_center+y,y_center-x,'ro')
plot(x_center-y,y_center-x,'ro')

