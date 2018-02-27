%% Plot the error and duration of q5

fileZeta = 'verification_zeta_mp.txt';
fileMach = 'verification_mach_mp.txt';

% Getting data of Zeta
fileID = fopen(fileZeta,'r');
Zeta = fscanf(fileID,'%f %f');
fclose(fileID);

% Getting data of Mach
fileID = fopen(fileMach,'r');
Mach = fscanf(fileID,'%f %f');
fclose(fileID);

%rescale the Matrices
Mach = [Mach(1:2:end),Mach(2:2:end)]
Zeta = [Zeta(1:2:end),Zeta(2:2:end)]
Mach'
%Plot the Data

figure;
subplot(2,1,1);
loglog(Mach(1,:)');
hold on
loglog(Zeta(1,:)');
legend('Error Mach','Error Zeta');

subplot(2,1,2);
loglog(Mach(2,:)');
hold on
loglog(Zeta(2,:)');
legend('Timing Mach','Timing Zeta');