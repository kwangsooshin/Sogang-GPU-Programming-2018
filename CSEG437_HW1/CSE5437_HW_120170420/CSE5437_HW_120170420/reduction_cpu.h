#pragma once

#include<stdlib.h>
#include<string.h>

void reduition_on_the_cpu(float *data, float *output, int n) {
	int i;
	float sum = 0.0f;

	for (i = 0; i < n; i++)
		sum += data[i];
	
	output[0] = sum;
}

void reduction_on_the_cpu_reduction(float* data, float *output, int n) {
	int i, j;
	float sum = 0.0f;

	float* data_b = (float*)malloc(sizeof(float)*n);
	memcpy(data_b, data, sizeof(float)*n);

	for (i = n / 2; i > 0; i >>= 1) {
		for (j = 0; j < i; j++) {
			data_b[j] += data_b[j + i];
		}
	}

	sum = data_b[0];
	free(data_b);
	
	output[0] = sum;
}

void reduction_on_the_CPU_KahanSum(float *data, float *output, int n) {
	int i;
	float sum = 0.0f, c = 0.0f, t, y;

	for (i = 0; i < n; i++) {
		y = data[i] - c;
		t = sum + y;
		c = (t - sum) - y;
		sum = t;
	}
	
	output[0] = sum;
}
