angle = [0:15:360];
stator_voltage_1_2 = [17 11 3 -4 -11 -20 -24 -28 -27 -25 -22 -17 -12 -6 0  ...
   6 12 18 22 25 26.6 26 24 20 15];
stator_voltage_2_3 = [15 19.2 22.5 26 28 27 23 18 12 4 1 -8 -13 -18 -22 -25 -26 ...
    -25.5 -23 -19 -15 -9 -1.5 4.5 11];
stator_voltage_3_1 = [-32 -30.4 -26 -22 -16 -6.5 0 9 15 21 24 25 26 6  ...
   -22 -19 -13 -7 0 4.5 11 17 21.5 25 26];
error_voltage = [0 1.4 3.2 5 6.2 8.2 8.6 8 7 5 3 1.2 0.2 1.8 3.6 5.4 7 8.2 ...
    8.8 8.4 7.2 6.1 3.6 1.8 0]
plot(angle,stator_voltage_1_2,'r');
hold on;
plot(angle,stator_voltage_2_3,'g');
hold on;
plot(angle,stator_voltage_3_1,'b');
hold on;
grid on;
xlabel('angluer position');
ylabel('stator voltage');
legend('stator_voltage_1_2','stator_voltage_3_2','stator_voltage_3_1');

