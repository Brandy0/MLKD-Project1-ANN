/*
   outtopgm - scale unit output weights to pixel values. 

 Example: Following creates .pgm file to display weights for output
          unit 2, from hidden layer containing 4 hidden units (plus threshold wt)
 outtopgm pose.net pose.pgm 5 1 2

 */
#include "stdafx.h"
#include <stdio.h>
#include <math.h>
#include "../facetrain/pgmimage.h"
#include "../facetrain/backprop.h"

#define MAXROWS 256
#define MAXCOLS 256

#define PGMROWS 120
#define PGMCOLS 128

double tmpimg;
double tmpweight = 0;

int _tmain(int argc, _TCHAR* argv[])
{
  BPNN *net;
  IMAGE *img;
  int nr, nc,  i, j, k, out, pxl;
  double maxwt, minwt, range;

  if (argc < 4) {
    fprintf(stderr, "usage:  %s net-file image-file output-unit-num hide-unit-num\n", argv[0]);
    exit(1);
  }

  if ((net = bpnn_read(argv[1])) == NULL) {
    fprintf(stderr, "%s:  can't read net-file '%s'\n", argv[0], argv[1]);
    exit(1);
  }
      
  out = atoi(argv[3]);
  int hn = atoi(argv[4]);
  if ((img = img_creat(argv[2], PGMROWS, PGMCOLS)) == NULL) {
    fprintf(stderr, "%s:  can't create image-file '%s'\n", argv[0], argv[2]);
    exit(1);
  }
      
  /* let the user in on the weight values */
  fprintf(stdout, "Output unit %s:\n Weight values: \n", argv[3]);  
  for (i = 0; i <= hn; i++) {
    printf("i=%d\n", i);
    fprintf(stdout, "  %g\n", net->hidden_weights[i][out]);
  }

  // add
  double outmap[PGMROWS][PGMCOLS];
  for (int i = 0; i < PGMROWS; i++) {
	  memset(outmap[i], net->hidden_weights[0][out], PGMCOLS * sizeof(double));
  }
  
  for (int hi = 1; hi <= hn; hi++) {
	  /* now scale values */
	  k = 0;
	  for (int i = 0; i < PGMROWS; i++) {
		  for (int j = 0; j < PGMCOLS; j++) {
			  tmpweight = net->input_weights[k][hi] * net->hidden_weights[hi][out];
			  outmap[i][j] += tmpweight;
			  k++;
		  }
	  }
  }

  /* first get min and max wts */
  maxwt = -1e6;
  minwt = 1e6;
  for (i = 0; i < PGMROWS; i++) {
	  for (j = 0; j < PGMCOLS; j++) {
		  if (outmap[i][j] > maxwt)
			  maxwt = outmap[i][j];
		  if (outmap[i][j] < minwt)
			  minwt = outmap[i][j];
	  }
  }
  range = maxwt - minwt;

  /* now scale values */
  k = 0;
  for (i = 0; i < PGMROWS; i++) {
    for (j = 0; j < PGMCOLS; j++) {
      tmpimg = outmap[i][j];
      pxl = ((tmpimg-minwt)/range) * 255.0;
	  img_setpixel(img, i, j, pxl);
      k++;
    }
  }

  img_write(img, argv[2]);
  return 0;
}
