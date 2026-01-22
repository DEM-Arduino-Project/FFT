# 📡 Arduino Fast Fourier Transform (FFT) Analyzer
> **Real-time signal processing and frequency analysis using the Adafruit ZeroFFT library.**

This project provides a robust implementation of the Fast Fourier Transform (FFT) algorithm on Arduino-compatible microcontrollers. It is designed to analyze signals in real-time, converting time-domain data into frequency-domain components to identify dominant frequencies. Whether you are analyzing audio, vibration, or synthetic signals, this tool offers a straightforward way to visualize and compute spectral data.

---

## 🚀 Key Features

*   **Real-time Signal Processing**: Capable of reading analog signals directly from an input pin (A0) and processing them on the fly.
*   **High-Speed FFT**: Utilizes the optimized `Adafruit_ZeroFFT` library for efficient computation on 32-bit microcontrollers (e.g., SAMD21/SAMD51).
*   **Dual Operation Modes**:
    *   **Live Mode**: Analyzes real-world signals from sensors or audio inputs.
    *   **Test Mode**: Uses hard-coded signal data (synthetic sine waves) for debugging and verification without external hardware.
*   **Dominant Frequency Detection**: Automatically calculates and outputs the frequency with the highest magnitude.
*   **Visualization Ready**: Formatted output compatible with the **Arduino Serial Plotter** for real-time graphical visualization of the spectrum.

---

## 🛠 Tech Stack

| Component | Technology / Protocol | Description |
| :--- | :--- | :--- |
| **Language** | C++ | Core implementation language for Arduino sketch. |
| **Framework** | Arduino SDK | Development platform and HAL. |
| **Library** | `Adafruit_ZeroFFT` | Optimized FFT library for ARM Cortex-M0/M4. |
| **Hardware** | Arduino (SAMD) | Recommended hardware (e.g., Arduino Zero, Feather M0). |
| **Input** | Analog ADC | signal acquisition via pin `A0`. |
| **Output** | UART / Serial | Data streaming at 9600 baud. |

---

## 🏗 Architecture & Design

The system operates on a cyclic processing model designed for continuous analysis:

1.  **Data Acquisition Phase**:
    *   The system collects `SAMPLE_SIZE` (default: 256) data points.
    *   In **Live Mode**, it samples the voltage at pin `A0`.
    *   In **Test Mode**, it loads pre-computed sine wave values from `signal.h`.
2.  **Processing Phase (FFT)**:
    *   The time-domain signal is passed to the `ZeroFFT` algorithm.
    *   The algorithm converts the signal into frequency bins.
3.  **Analysis Phase**:
    *   The system iterates through the frequency bins (up to `SAMPLING_RATE / 2`).
    *   It calculates the magnitude for each bin and tracks the maximum value to identify the **Dominant Frequency**.
4.  **Output Phase**:
    *   Results (Frequency vs. Amplitude) are sent over Serial for logging or plotting.

> **Note**: The code uses a "blocking" read mechanism for simplicity, ensuring signal continuity during the sampling window.

---

## 🔌 Prerequisites & Installation

### Hardware Requirements
*   Arduino Zero, Feather M0, or any SAMD21/SAMD51 based board. (Note: `Adafruit_ZeroFFT` is optimized for these architectures).
*   Signal source (Function generator, Microphone amplifier, or simple wire for noise testing).

### Software Setup
1.  **Install Arduino IDE**: Download from [arduino.cc](https://www.arduino.cc/en/software).
2.  **Install Library**:
    *   Open Arduino IDE.
    *   Go to **Sketch** -> **Include Library** -> **Manage Libraries...**
    *   Search for **Adafruit ZeroFFT** and install the latest version.

### Installation Steps
1.  Clone this repository:
    ```bash
    git clone https://github.com/your-username/FFT-Arduino-Project.git
    ```
2.  Open the `FFT.ino` file in the Arduino IDE.
3.  Select your board and port in **Tools** -> **Board** / **Port**.

---

## 💻 Usage

### 1. Configuration
Open `FFT.ino` and modify the configuration macros at the top of the file to suit your needs:

```cpp
// Set to 1 to use internal test data, 0 for real sensor data
#define USE_HARD_CODED_DATA 0 

// Set the sample rate (must match your actual sampling frequency)
#define SAMPLING_RATE 80 

// FFT Size (Power of 2, e.g., 256, 512)
#define SAMPLE_SIZE 256 
```

### 2. Running the Analyzer
1.  Connect your analog signal source to **Pin A0** (if using `USE_HARD_CODED_DATA 0`).
2.  **Upload** the sketch to your board.
3.  Open the **Serial Plotter** (`Ctrl+Shift+L`) to see the frequency spectrum visually.
4.  Alternatively, open the **Serial Monitor** (`Ctrl+Shift+M`) at **9600 baud** to see textual data and the calculated dominant frequency.

### Example Output
```text
30 Hz: 12.50
31 Hz: 45.10
...
Dominant frequency: 31.00 Hz
```

---

## 📊 MATLAB Verification

This project includes a MATLAB script to verify the accuracy of the Arduino FFT implementation. You can use it to compare the on-board processing results with a high-precision reference.

### Files
*   `Matlab_code/Arduino_FFT_Spectral.m`: The main script for offline FFT analysis.
*   `Matlab_code/Input_Signal.mat`: Pre-recorded test signal data.
*   `Matlab_code/Input.txt`: Text version of the signal data.

### How to Run
1.  Open **MATLAB**.
2.  Navigate to the `Matlab_code/` directory.
3.  Load the signal data:
    ```matlab
    load('Input_Signal.mat'); % Loads 'Input_Signal' variable into workspace
    ```
4.  Run the validation script:
    ```matlab
    Arduino_FFT_Spectral
    ```
5.  A plot will appear showing the **Single-Sided Amplitude Spectrum**. Compare the peak frequency and amplitude distribution with your Arduino Serial Plotter results to validate the implementation.

> **Note**: The MATLAB script assumes a sampling frequency (`Fs`) of **8000 Hz** (matching the data generation). Ensure your Arduino implementation is configured correctly to match or account for this when comparing.


---

## 🔮 Future Improvements

Here is the roadmap for future development:

*   [ ] **Dynamic Sampling Rate**: Implement interrupt-based sampling for more precise timing.
*   [ ] **OLED/LCD Integration**: Display the dominant frequency directly on a screen.
*   [ ] **Noise Filtering**: Add software filters (e.g., Moving Average) before FFT processing.
*   [ ] **Windowing Functions**: Implement Hanning or Hamming windows to reduce spectral leakage.
*   [ ] **Optimized Storage**: Use DMA (Direct Memory Access) for signal acquisition to free up CPU time.

---
*Created by [Your Name]*
