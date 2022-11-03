clear all
close all
clc

%% Load the signal and find the peaks using findpeaks

audio = load('TEST.txt');
audio = audio - mean(audio);
n = length(audio);
fs = 0.98; %sampling frequency  
ts = 1/fs;
t = 1 : n;
t = t/fs;
[pks,locs] = findpeaks(audio);
locs = locs/fs;
figure;
plot(t,audio);
hold on;
plot(locs,pks,'*');
xlabel('time [s]');
ylabel('ADC value');
title ('Audio Signal');
legend('Breathing audio signal','Peaks');

%% Filtering

fcut = 0.9;
Wn = fcut/fs;
[d,c] = butter(3,Wn,'low');
audio_filt = filtfilt(d,c,audio);
figure;
plot(t,audio_filt);
title ('Filtred signal');

%% findpeaks of the filtered signal 

[pks2,locs2]=findpeaks(audio_filt); 
locs2 = locs2/fs;
figure;
plot(t,audio_filt);
hold on;
plot(locs2,pks2,'*');
%xlabel('time [s]');
%ylabel('ADC value');
title('Filtred Signal with Peaks');
legend('Filtred signal','Peaks');
xlim([74 92]);

%% find the local minimums of the filtered signal

min = islocalmin(audio_filt);
figure;
plot(t,audio_filt);
hold on;
plot(t(min),audio_filt(min),'*');
hold on;
plot(locs2,pks2,'*');

%% Calculate the respiration rate 

sum = length(pks2)+length(audio_filt(min));
count = sum/2;