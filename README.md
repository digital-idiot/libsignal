# libsignal
C library providing some basic functions for signal processing

#Overview
* Some key functions of this library:
  * Matrix Manipulation
    * Transpose
    * Inverse
  * Vector Manipulation
    * Vector Addition
    * Vector Substruction
    * Dot Product
    * Division
  * Numerical Functions
    * Polyfit(Using LSF)
    * Polyval
  * Filters
    * Low Pass
    * High Pass
    * Band Pass
    *Band Stop
  * Windowing
    * Rectangular
    * Bartlett
    * Hanning
    * Hamming
    * Blackman
  * Fast Fourrier Transformation

#Note
This library is developed targeting the **TMS320F28377D** DSP.
A sample program is included. Output of the sample program is plotted using GNU-plot. GNU-plot script can be found inside 'testout' folder. Below is output graph.

![Alt text](/testout/graph.png?raw=true "Graph")


***This is a part of my SRIP-2016 project at IIT-Gandhinagar.***
