#include<math.h>
#include<fftw3.h>
#include<complex.h>
#include<stdlib.h>
#include "numericals.h"
#include "signals.h"

vector filter(vector coeff, vector h) //simple FIR filter
{
	vector y;
	y.array = NULL;
	y.l = 0;
	if((coeff.l!=0)&&(coeff.array!=NULL)&&(h.l!=0)&&(h.array!=NULL))
	{
		size_t index = 0;
		double* buf = malloc(h.l*sizeof(double));
		for(size_t i=0;i<h.l;i++)
		{
			buf[i] = 0.0;
		}
		while(index<coeff.l)
		{
			double sum = 0;
			for(size_t i=h.l;i>1;i--)
			{
				buf[i-2] = buf[i-1];
			}
			buf[0] = coeff.array[index];
			for(size_t i=0;i<h.l;i++)
			{
				sum = sum + (buf[i] * h.array[i]);
			}
			y.array = realloc(y.array,(y.l+1)*sizeof(double));
			y.array[y.l] = sum;
			y.l++;
			index++;
		}
		free(buf);
	}
	return y;
}

int outputFFT(char *filename, double *window, size_t windowLength, double sampFreq)
{	
	int i;
	FILE *fp;
	double *in;
	fftw_complex *out;
	fftw_plan plan;
	int result = 0;
	int flag = 0;

	// If the window length is short, zero padding will be used
	int fftSize = (windowLength < 2048) ? 2048 : windowLength;

	// Calculate size of result data
	int resultSize = (fftSize / 2) + 1;

	// Allocate memory to hold input and output data
	in = (double *) fftw_malloc(fftSize * sizeof(double));
	out = (fftw_complex *) fftw_malloc(resultSize * sizeof(fftw_complex));
	if (in == NULL || out == NULL) {
		result = 1;
		fprintf(stderr, "outputFFT: Could not allocate input/output data\n");
		flag = 1;
	}

	if(flag==0)
	{
		// Create the plan and check for success
		plan = fftw_plan_dft_r2c_1d(fftSize, in, out, FFTW_MEASURE); 
		if (plan == NULL)
		{
			result = 1;
			fprintf(stderr, "outputFFT: Could not create plan\n");
			flag = 1;
		}
		
		if(flag==0)
		{

			// Copy window and add zero padding (if required)
			for (i=0 ; i<(int)windowLength ; i++)
				in[i] = window[i];
			for ( ; i<fftSize ; i++)
				in[i] = 0;
	
			// Perform fft
			fftw_execute(plan);

			// Open file for writing
			fp = fopen(filename, "w");
			if (fp == NULL)
			{
				result = 1;
				fprintf(stderr, "outputFFT: Could open output file for writing\n");
				flag = 1;
			}

			if(flag==0)
			{
				// Output result
				for (i=0 ; i<resultSize ; i++)
				{
					double freq = sampFreq * i / fftSize;
					double mag = sqrt(out[i][0] * out[i][0] + out[i][1] * out[i][1]);
					double magdB = 20 * log10(mag);
					double phase = atan2(out[i][1], out[i][0]);
					fprintf(fp, "%02d %f %f %f %f\n", i, freq, mag, magdB, phase);
				}
			}
		}
	}

	// Perform any cleaning up
	if (plan != NULL) fftw_destroy_plan(plan);
	if (in != NULL) fftw_free(in);
	if (out != NULL) fftw_free(out);
	if (fp != NULL) fclose(fp);

	return result;
}


// Create sinc function for filter with 1 transition - Low and High pass filters
double *create1TransSinc(size_t windowLength, double transFreq, double sampFreq, enum filterType type)
{
	int n;

	// Allocate memory for the window
	double *window = (double *) malloc(windowLength * sizeof(double));
	if (window == NULL) {
		fprintf(stderr, "create1TransSinc: Could not allocate memory for window\n");
		return NULL;
	}

	if (type != LOW_PASS && type != HIGH_PASS) {
		fprintf(stderr, "create1TransSinc: Bad filter type, should be either LOW_PASS of HIGH_PASS\n");
		return NULL;
	}

	// Calculate the normalised transistion frequency. As transFreq should be
	// less than or equal to sampFreq / 2, ft should be less than 0.5
	double ft = transFreq / sampFreq;

	double m_2 = 0.5 * (windowLength-1);
	int halfLength = (int)windowLength / 2;

	// Set centre tap, if present
	// This avoids a divide by zero
	if (2*halfLength != (int)windowLength)
	{
		double val = 2.0 * ft;

		// If we want a high pass filter, subtract sinc function from a dirac pulse
		if (type == HIGH_PASS) val = 1.0 - val;

		window[halfLength] = val;
	}
	else if (type == HIGH_PASS) {
		fprintf(stderr, "create1TransSinc: For high pass filter, window length must be odd\n");
		return NULL;
	}

	// This has the effect of inverting all weight values
	if (type == HIGH_PASS) ft = -ft;

	// Calculate taps
	// Due to symmetry, only need to calculate half the window
	for (n=0 ; n<halfLength ; n++) {
		double val = sin(2.0 * M_PI * ft * (n-m_2)) / (M_PI * (n-m_2));

		window[n] = val;
		window[windowLength-n-1] = val;
	}

	return window;
}

// Create two sinc functions for filter with 2 transitions - Band pass and band stop filters
double *create2TransSinc(size_t windowLength, double trans1Freq, double trans2Freq, double sampFreq, enum filterType type)
{
	int n;

	// Allocate memory for the window
	double *window = (double *) malloc(windowLength * sizeof(double));
	if (window == NULL) {
		fprintf(stderr, "create2TransSinc: Could not allocate memory for window\n");
		return NULL;
	}

	if (type != BAND_PASS && type != BAND_STOP) {
		fprintf(stderr, "create2TransSinc: Bad filter type, should be either BAND_PASS or BAND_STOP\n");
		return NULL;
	}

	// Calculate the normalised transistion frequencies.
	double ft1 = trans1Freq / sampFreq;
	double ft2 = trans2Freq / sampFreq;

	double m_2 = 0.5 * (windowLength-1);
	int halfLength = (int)windowLength / 2;

	// Set centre tap, if present
	// This avoids a divide by zero
	if (2*halfLength != (int)windowLength) {
		double val = 2.0 * (ft2 - ft1);

		// If we want a band stop filter, subtract sinc functions from a dirac pulse
		if (type == BAND_STOP) val = 1.0 - val;

		window[halfLength] = val;
	}
	else {
		fprintf(stderr, "create1TransSinc: For band pass and band stop filters, window length must be odd\n");
		return NULL;
	}

	// Swap transition points if Band Stop
	if (type == BAND_STOP) {
		double tmp = ft1;
		ft1 = ft2; ft2 = tmp;
	}

	// Calculate taps
	// Due to symmetry, only need to calculate half the window
	for (n=0 ; n<halfLength ; n++) {
		double val1 = sin(2.0 * M_PI * ft1 * (n-m_2)) / (M_PI * (n-m_2));
		double val2 = sin(2.0 * M_PI * ft2 * (n-m_2)) / (M_PI * (n-m_2));

		window[n] = val2 - val1;
		window[windowLength-n-1] = val2 - val1;
	}

	return window;
}

// Create a set of window weights
// in - If not null, each value will be multiplied with the window weight
// out - The output weight values, if NULL and new array will be allocated
// windowLength - the number of weights
// windowType - The window type
double *createWindow(double *in, double *out, size_t windowLength, enum windowType type)
{
	// If output buffer has not been allocated, allocate memory now
	if (out == NULL) {
		out = (double *) malloc(windowLength * sizeof(double));
		if (out == NULL) {
			fprintf(stderr, "Could not allocate memory for window\n");
			return NULL;
		}
	}

	int n;
	int m = (int)windowLength - 1;
	int halfLength = (int)windowLength / 2;

	// Calculate taps
	// Due to symmetry, only need to calculate half the window
	switch (type)
	{
		case RECTANGULAR:
			for (n=0 ; n<(int)windowLength ; n++) {
				out[n] = 1.0;
			}
			break;

		case BARTLETT:
			for (n=0 ; n<=halfLength ; n++) {
				double tmp = (double) n - (double)m / 2;
				double val = 1.0 - (2.0 * fabs(tmp))/m;
				out[n] = val;
				out[windowLength-n-1] = val;
			}

			break;

		case HANNING:
			for (n=0 ; n<=halfLength ; n++) {
				double val = 0.5 - 0.5 * cos(2.0 * M_PI * n / m);
				out[n] = val;
				out[windowLength-n-1] = val;
			}

			break;

		case HAMMING:
			for (n=0 ; n<=halfLength ; n++) {
				double val = 0.54 - 0.46 * cos(2.0 * M_PI * n / m);
				out[n] = val;
				out[windowLength-n-1] = val;
			}
			break;

		case BLACKMAN:
			for (n=0 ; n<=halfLength ; n++) {
				double val = 0.42 - 0.5 * cos(2.0 * M_PI * n / m) + 0.08 * cos(4.0 * M_PI * n / m);
				out[n] = val;
				out[windowLength-n-1] = val;
			}
			break;
	}

	// If input has been given, multiply with out
	if (in != NULL) {
		for (n=0 ; n<(int)windowLength ; n++) {
			out[n] *= in[n];
		}
	}

	return out;
}

// Transition Width (transWidth) is given in Hz
// Sampling Frequency (sampFreq) is given in Hz
// Window Length (windowLength) will be set
void calculateKaiserParams(double ripple, double transWidth, double sampFreq, size_t *windowLength, double *beta)
{
	// Calculate delta w
	double dw = 2 * M_PI * transWidth / sampFreq;

	// Calculate ripple dB
	double a = -20.0 * log10(ripple);

	// Calculate filter order
	int m;
	if (a>21) m = ceil((a-7.95) / (2.285*dw));
	else m = ceil(5.79/dw);

	*windowLength = (size_t)(m + 1);

	if (a<=21) *beta = 0.0;
	else if (a<=50) *beta = 0.5842 * pow(a-21, 0.4) + 0.07886 * (a-21);
	else *beta = 0.1102 * (a-8.7);
}

double modZeroBessel(double x)
{
	int i;

	double x_2 = x/2;
	double num = 1;
	double fact = 1;
	double result = 1;

	for (i=1 ; i<20 ; i++) {
		num *= x_2 * x_2;
		fact *= i;
		result += num / (fact * fact);
		//printf("%f %f %f\n", num, fact, result);
	}

	return result;
}

double *createKaiserWindow(double *in, double *out, size_t windowLength, double beta)
{
	double m_2 = (double)(windowLength-1) / 2.0;
	double denom = modZeroBessel(beta);					// Denominator of Kaiser function

	// If output buffer has not been allocated, allocate memory now
	if (out == NULL) {
		out = (double *) malloc(windowLength * sizeof(double));
		if (out == NULL) {
			fprintf(stderr, "Could not allocate memory for window\n");
			return NULL;
		}
	}

	int n;
	for (n=0 ; n<(int)windowLength ; n++)
	{
		double val = ((n) - m_2) / m_2;
		val = 1 - (val * val);
		out[n] = modZeroBessel(beta * sqrt(val)) / denom;
	}

	// If input has been given, multiply with out
	if (in != NULL) {
		for (n=0 ; n<(int)windowLength ; n++) {
			out[n] *= in[n];
		}
	}

	return out;
}

vector hilo_filterWindow(size_t windowLength, double transFreq, double sampFreq, enum filterType ftype, enum windowType wtype)
{
	vector window;
	double *hlf = create1TransSinc(windowLength, transFreq, sampFreq, ftype);
	window.l = windowLength;
	window.array = createWindow(hlf, NULL, windowLength, wtype);
	return window;
}

vector bps_filterWindow(size_t windowLength, double trans1Freq, double trans2Freq, double sampFreq, enum filterType ftype)
{
	vector window;
	double *psf = create2TransSinc(windowLength, trans1Freq, trans2Freq, sampFreq, ftype);
	window.l = windowLength;
	window.array = createWindow(psf, NULL, windowLength, HAMMING);
	return window;
}

vector kl_filterWindow(double ripple, double transWidth, double transFreq, double sampFreq)
{
	vector window;
	size_t kaiserWindowLength;
	double beta;
	calculateKaiserParams(ripple, transWidth, sampFreq, &kaiserWindowLength, &beta);
	double *lpf = create1TransSinc(kaiserWindowLength, transFreq, sampFreq, LOW_PASS);
	window.l = (size_t)kaiserWindowLength;
	window.array = createKaiserWindow(lpf, NULL, kaiserWindowLength, beta);
	return window;
}

plotdata findpeaks(plotdata pd, double minpdist) //return peaks
{
	plotdata peaks;
	peaks.y = NULL;
	peaks.x = NULL;
	size_t j=0,k=1;
	for(size_t i=0;(i+2)<pd.length;i=i+k)
	{
		k = 1;
		if((pd.y[i+1]>=pd.y[i])&&(pd.y[i+1]>=pd.y[i+2]))
		{
			peaks.y = realloc(peaks.y,(j + 1)*sizeof(double));
			peaks.x = realloc(peaks.x,(j + 1)*sizeof(double));
			peaks.y[j] = pd.y[i + 1];
			peaks.x[j] = pd.x[i + 1];
			j++;
			while(((i+k+1)<pd.length)&&((pd.x[i+k+1]-pd.x[i+1])<minpdist))
			{
				k++;
			}
		}
	}
	peaks.length = j;
	return peaks;
}

twodpoint* p_min(plotdata pd)
{
	twodpoint *p;
	p = NULL;
	if((pd.length!=0)&&(pd.x!=NULL)&&(pd.y!=NULL))
	{
		p = malloc(sizeof(twodpoint));
		p->yy = pd.y[0];
		p->xx = pd.x[0];
		for(size_t i=1;i<pd.length;i++)
		{
			if((p->yy)>pd.y[i])
			{
				p->yy = pd.y[i];
				p->xx = pd.x[i];
			}
		}
	}
	return p;
}

plotdata xplotify(vector vect)
{
	plotdata pd;
	pd.length = 0;
	pd.x = NULL;
	pd.y = NULL;
	if((vect.l!=0)&&(vect.array!=NULL))
	{
		pd.length = vect.l;
		pd.y = vect.array;
		pd.x = (genseries(1.0,pd.length,1.0)).array;
	}
	return pd;
}
