#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

constexpr int ARRAY_SIZE = 14748364;
float x[ARRAY_SIZE], y[ARRAY_SIZE];

int main(int argc, char *argv[]) {
  int i, j, is_cpu = true;
  double tstart, tstop;
  float a = 1.5f;
  float tolerance = 0.01f;
  int correct_count = 0;

  // Initialize some data
  for (i = 0; i < ARRAY_SIZE; i++) {
    x[i] = (float)i;
    y[i] = (float)i;
  }

  tstart = omp_get_wtime();

#include "saxpy_func.cpp"

  tstop = omp_get_wtime();
  printf("Work took %f seconds\n", tstop - tstart);

  printf("Running on %s.\n", is_cpu ? "CPU" : "GPU");

  for (int i = 0; i < ARRAY_SIZE; i++)
    if (abs(y[i] - (a * i + i)) < tolerance)
      correct_count++;
    else {
      printf("Incorrect Result at Element [%d] : %f", i, y[i]);
      break;
    }
  printf("Test: %s\n", (correct_count == ARRAY_SIZE) ? "PASSED!" : "Failed");
}

