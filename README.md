# **redmoon v0.1.0**

redmoon is an engaging and fun music visualizer application built using C++23 and the SDL3 library. It aims to provide a visually stimulating experience that reacts dynamically to audio input, based on the requirements outlined [here](http://docs.google.com/link_to_requirements_doc_if_available).

## **Features (Planned/Implemented based on Requirements)**

* **SDL3 Powered:** Utilizes the latest SDL3 library for cross-platform windowing, rendering, audio, and event handling.  
* **Multiple Audio Inputs:** Supports playback from audio files (MP3, WAV, OGG, FLAC) and potentially real-time input from system audio or microphone.  
* **Real-time Audio Analysis:** Employs FFT for frequency analysis and calculates amplitude to drive visualizations. Beat detection may be included.  
* **Diverse Visualizers:** Offers various visualization modes like spectrum bars, waveforms, particle systems, geometric patterns, and abstract art.  
* **Customization:** Allows users to select color palettes, backgrounds, and tweak visualizer parameters.  
* **Modern C++:** Written in C++23.

## **Dependencies**

* **CMake** (Version 3.26.0 or higher)  
* **C++23 compatible compiler** (e.g., GCC, Clang, MSVC)  
* **SDL3**  
* **SDL3\_image**  
* **SDL3\_ttf**  
* **SDL3\_mixer**

*Note:* If the SDL3 libraries (and their development headers) are not found on your system, CMake will attempt to download and build them automatically using the FetchContent module. They will be placed in the vendor directory within the source tree.

## **Building**

1. **Clone the repository:**  
   git clone \<your-repository-url\>  
   cd redmoon

2. **Create a build directory:**  
   cmake \-S . \-B build

   * This command configures the project and generates build files in the build directory. CMake will check for dependencies and fetch them if necessary.  
3. **Compile the project:**  
   cmake \--build build

   * Alternatively, navigate into the build directory (cd build) and run your build system's command (e.g., make, ninja).

## **Running**

The executable will be located in the build/bin directory:

./build/bin/redmoon

The application requires resource files (like fonts, images, default settings) to be present. The build process automatically copies the contents of the res directory from the source tree to build/bin/res. Ensure this res directory is alongside the redmoon executable when running it.

## **Project Structure**

* src/: Contains the C++ source code.  
  * redmoon.cpp: Main application file (likely).  
* res/: Contains resource files (fonts, images, shaders, etc.).  
* vendor/: (Created by CMake if dependencies are fetched) Contains downloaded source code for dependencies.  
* CMakeLists.txt: The main CMake build script.  
* build/: (Created by you) Contains the build files and output binaries.
