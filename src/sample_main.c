#include <stdio.h>
#include "structures.h"
#include "vectors.h"
#include "matrices.h"
#include "struct_ops.h"
#include "numericals.h"
#include "signals.h"

int main()
{
	size_t windowLength = 201;
	double sampFreq = 44100;

	// Low Pass & High Pass filters
	double transFreq = 10000;
	vector hpf_hamming = hilo_filterWindow(windowLength, transFreq, sampFreq, HIGH_PASS, HAMMING);
	vector lpf_hamming = hilo_filterWindow(windowLength, transFreq, sampFreq, LOW_PASS, HAMMING);
	vector lpf_blackman = hilo_filterWindow(windowLength, transFreq, sampFreq, LOW_PASS, BLACKMAN);
	outputFFT("../testout/lpf-hamming.dat", lpf_hamming.array, windowLength, sampFreq);
	outputFFT("../testout/lpf-blackman.dat", lpf_blackman.array, windowLength, sampFreq);
	outputFFT("../testout/hpf-hamming.dat", hpf_hamming.array, windowLength, sampFreq);

	
	double trans1Freq = 5000;
	double trans2Freq = 17050;
	
	//Band Pass & Band Stop filters
	vector bpf_hamming = bps_filterWindow(windowLength, trans1Freq, trans2Freq, sampFreq, BAND_PASS);
	vector bsf_hamming = bps_filterWindow(windowLength, trans1Freq, trans2Freq, sampFreq, BAND_STOP);
	outputFFT("../testout/bpf-hamming.dat", bpf_hamming.array, windowLength, sampFreq);
	outputFFT("../testout/bsf-hamming.dat", bsf_hamming.array, windowLength, sampFreq);
	
	return 0;
}
