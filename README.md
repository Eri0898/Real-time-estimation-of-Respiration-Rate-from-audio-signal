# Real-time-estimation-of-Respiration-Rate-from-audio-signal

- In the [Matlab algorithm](https://github.com/Eri0898/Real-time-estimation-of-Respiration-Rate-from-audio-signal/blob/main/Matlab_algorithm.m) a Matlab script for the estimation of the Respiration Rate from audio respiratory signals is implemented. In this script the Respiration Rate is simply counted by loading the respiratory signal, filtering it and counting its peaks. 
- The [Arduino algorithm](https://github.com/Eri0898/Real-time-estimation-of-Respiration-Rate-from-audio-signal/blob/main/Arduino_algorithm.ino) script shows a way to count the breaths done in a certain interval using Arduino IDE and an Arduino Uno board with a Grove-Sound Sensor mounted on it. In this simple algorithm, the count of the Respiration Rate is done by firstly recognizing if the subject performs long or normal breaths. In fact the first part of the counting function consists in counting how much breaths the subject does in the first 10 seconds of acquisition. If the breaths done in 10 seconds are less or equal to 2, then the subject performs long breaths and in this case the count is performed by comparing each sample with the previous, the next, two previous and two subsequent samples. Instead, if the breaths done in 10 seconds are greater than 2, the subject performs normal breaths and the count is performed by comparing each sample with the previous, the next ones. In both cases, the signal is filtered during the acquisition.
