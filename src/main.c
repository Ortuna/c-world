#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <complex.h>

// #include <liquid.h>

void generate_sin(long double *t, int t_len, float sr, int freq_hz) {
  for(int i = 0; i < t_len; i++) {
    t[i] = sr * i;
    t[i] = sin(t[i] * 2 * M_PI * freq_hz);
  }
}

void write_file(char *str, long double complex *data, int data_len) {
  FILE *file = fopen(str, "w");

  for(int i = 0; i < data_len; i++) {
    fprintf(file, "%d %Lf\n", i, creall(data[i]));
  }

  fclose(file);
}

void write_file_raw(char *str, long double *data, int data_len) {
  FILE *file = fopen(str, "w");

  for(int i = 0; i < data_len; i++) {
    fprintf(file, "%d %Lf\n", i, data[i]);
  }

  fclose(file);
}

void add_signal(long double *x, long double *y, long double *output, int data_len) {
  for(int i = 0; i < data_len; i++) {
    output[i] = x[i] + y[i];
  }
}

long double calc_exp(long double x, int k, int n, int N) {
  long double p = (float)k * ((float) n / (float)N) * 2 * M_PI;

  return x * (cos(p) - (sin(p) * I));
}

void simple_fft(long double *x, long double complex *y, int sample_bw) {
  for(int k = 0; k < sample_bw / 2; k++) {
    for(int n = 0; n < sample_bw / 2; n++) {
      y[k] += calc_exp(x[n], k, n, sample_bw);
    }
  }
}

void simple_ifft(long double complex *x, long double complex *y, int sample_bw) {
  for(int k = 0; k < sample_bw / 2; k++) {
    for(int n = 0; n < sample_bw / 2; n++) {
      y[k] += calc_exp(x[n], k, n, sample_bw);
    }
  }
}

void block_freq(long double complex *x, int sample_bw) {
  for(int k = 0; k < sample_bw / 2; k++) {
    if(k < 40) {
      x[k] = 0;
    }
  }
}

int main() {
  int   sample_num  = 1;
  int   sample_bw = 1000;

  int    data_len = sample_bw * sample_num;
  long double *hz_60  = calloc(sizeof(long double), data_len);
  long double *hz_30  = calloc(sizeof(long double), data_len);
  long double *output = calloc(sizeof(long double), data_len);

  generate_sin(hz_60, data_len, 1.0/sample_bw, 60);
  generate_sin(hz_30, data_len, 1.0/sample_bw, 30);

  add_signal(hz_60, hz_30, output, data_len);

  long double complex *fft = calloc(sizeof(long double complex), sample_bw / 2);
  simple_fft(output, fft, sample_bw);

  block_freq(fft, sample_bw);

  long double complex *ifft = calloc(sizeof(long double complex), sample_bw / 2);
  simple_ifft(fft, ifft, sample_bw);

  write_file("./build/output.txt", ifft, sample_bw / 2);

  free(hz_60);
  free(hz_30);
  free(fft);
  free(output);
}
