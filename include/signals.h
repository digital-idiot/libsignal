#ifndef SIGNALS_H_   /* Include guard */
#define SIGNALS_H_

#include "structures.h"
#include "vectors.h"
#include "matrices.h"


enum filterType {LOW_PASS, HIGH_PASS, BAND_PASS, BAND_STOP};

enum windowType {RECTANGULAR, BARTLETT, HANNING, HAMMING, BLACKMAN};


vector filter(vector coeff, vector h); //simple FIR filter 

vector hilo_filterWindow(size_t windowLength, double transFreq, double sampFreq, enum filterType ftype, enum windowType wtype);

vector bps_filterWindow(size_t windowLength, double trans1Freq, double trans2Freq, double sampFreq, enum filterType ftype);

vector kl_filterWindow(double ripple, double transWidth, double transFreq, double sampFreq);

int outputFFT(char *filename, double *window, size_t windowLength, double sampFreq);

plotdata findpeaks(plotdata pd, double minpdist); //return peaks

twodpoint* p_min(plotdata pd);

plotdata xplotify(vector vect);

#endif
