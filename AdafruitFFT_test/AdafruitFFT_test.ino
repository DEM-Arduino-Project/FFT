/* This example shows the most basic usage of the Adafruit ZeroFFT library.
 * it calculates the FFT and prints out the results along with their corresponding frequency
 * 
 * The signal.h file constains a 200hz sine wave mixed with a weaker 800hz sine wave.
 * The signal was generated at a sample rate of 8000hz.
 * 
 * Note that you can print only the value (coment out the other two print statements) and use
 * the serial plotter tool to see a graph.
 */

#include "Adafruit_ZeroFFT.h"
#include "signal.h"

//the signal in signal.h has 2048 samples. Set this to a value between 16 and 2048 inclusive.
//this must be a power of 2
#define DATA_SIZE 256

//the sample rate
#define SAMPLING_RATE 8000
#define CHANNEL A0

#define USE_HARD_CODED_DATA 1

q15_t analog_signal_data[DATA_SIZE];

// the setup routine runs once when you press reset:
void setup() {

  Serial.begin(9600);
  while(!Serial); //wait for serial to be ready

  //run the FFT
  if(USE_HARD_CODED_DATA)
    ZeroFFT(hard_coded_signal_data, DATA_SIZE); 
  else
    ZeroFFT(analog_signal_data, DATA_SIZE);

  //data is only meaningful up to sample rate/2, discard the other half
  for(int i=0; i<DATA_SIZE/2; i++){
    
    //print the frequency
    Serial.print(FFT_BIN(i, SAMPLING_RATE, DATA_SIZE));
    Serial.print(" Hz: ");

    //print the corresponding FFT output
    if(USE_HARD_CODED_DATA)
      Serial.println(hard_coded_signal_data[i]);
    else
      Serial.println(analog_signal_data[i]);
    
  }

  if(USE_HARD_CODED_DATA){
    float max_amplitude = 0;
    float dominant_frequency = 0;

    // iterate through the FFT bins to find the dominant frequency
    for(int i=0; i<DATA_SIZE/2; i++) {
        if(hard_coded_signal_data[i] > max_amplitude) {
            max_amplitude = hard_coded_signal_data[i];
            dominant_frequency = FFT_BIN(i, SAMPLING_RATE, DATA_SIZE);
        }
    }

    Serial.print("Dominant frequency: ");
    Serial.print(dominant_frequency);
    Serial.println(" Hz");
    }
}

void loop() {
  //don't even do anything
}

void read_signal_data()
{
  for(int i=0; i<DATA_SIZE; i++)
  {
    // read data from pin A0
    int sensor_read = analogRead(CHANNEL);
    analog_signal_data[i] = (sensor_read + 0.5) * (5.0 / 1023.0);
  }
}

