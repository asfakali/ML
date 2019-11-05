clear all;
close all;
clc;

n=0:10;
x = n.*(.05).^n;
k = 0:200;
w = k * (pi/100);
X = x * (exp(-j*pi/100)).^(n'*k);
magX = abs(X)
angleX = angle(X);
subplot(2,1,1);
plot(w,magX);
grid;
axis([0,6,0,0.06])
ylabel('|X|');
xlabel('frequency unit of pi--->');
title('Magnitude plot');
subplot(2,1,2);
plot(w/pi,angleX/pi);
grid;
axis([0,2,-1,1])
ylabel('radians/pi');
xlabel('frequency unit of pi--->');
title('Angle plot');