% Add sampling Frequency
Fs = 8000;
% Compute sampling period as the inverse of the sampling frequency
Ts = 1/Fs;
% Compute the vector length of the input signal
Vector_Length = length(Input_Signal);
% Create the time vector, one step is one sampling period
% If the time vector starts from zero, always use (Vector_Length - 1)
% multiplied by the step, meaning multiplied by the sampling period
t = 0:Ts:(Vector_Length-1)*Ts;
% Always use column vectors;
t = t';
% Compute FFT of the input signal
FFT_Signal = fft(Input_Signal);
% Important, always normalize the computef fft by the vector length,
% meaning you divide the computed fft vector by the vector length
FFT_Signal = FFT_Signal/Vector_Length;
% The number of unique points in the computed fft vector is always equal to
% ceil((Vector_Length)/2)
Unique_Points = ceil((Vector_Length+1)/2);
% Retain only the single sided part of the signal
Single_Sided_FFT_Signal = FFT_Signal(1:Unique_Points);
% Compute the amplitude vector of the single sided vector
Single_Sided_Amplitude_Vector = abs(Single_Sided_FFT_Signal);
% Double the computed amplitude depending on if the signal number of
% elements is even or odd
if mod(Vector_Length,2) == 0
    Single_Sided_Amplitude_Vector(2:Unique_Points-1) = Single_Sided_Amplitude_Vector(2:Unique_Points-1)*2;
else
    Single_Sided_Amplitude_Vector(2:Unique_Points) = Single_Sided_Amplitude_Vector(2:Unique_Points)*2;
end
% Compute the frequency vector, the number of elements in the frequency
% vector always has to be equal to the number of fft unique elements
Single_Sided_Frequency_Vector = 0:Fs/Vector_Length:Fs/2;
% Again, always use column vectors
Single_Sided_Frequency_Vector = Single_Sided_Frequency_Vector';
% Plot the frequency vector as horizontal axis and
% plot the computed single sided amplitude vector
plot(Single_Sided_Frequency_Vector,Single_Sided_Amplitude_Vector);
title('Single Sided Amplitude')
xlabel('Frequency (Hz)')
ylabel('Amplitude')