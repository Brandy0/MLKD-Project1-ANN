/*
 ******************************************************************
 * HISTORY
 * 15-Oct-94  Jeff Shufelt (js), Carnegie Mellon University
 *      Prepared for 15-681, Fall 1994.
 *
 ******************************************************************
 */

#include "stdafx.h"

#include <stdio.h>
#include "pgmimage.h"
#include "backprop.h"

#include "FaceTrain.h"

extern void exit();

#define TARGET_HIGH 0.9
#define TARGET_LOW 0.1


/*** This is the target output encoding for a network with one output unit.
     It scans the image name, and if it's an image of me (js) then
     it sets the target unit to HIGH; otherwise it sets it to LOW.
     Remember, units are indexed starting at 1, so target unit 1
     is the one to change....  ***/

void load_target(IMAGE *img,BPNN *net)
{
  int scale;
  char userid[40], head[40], expression[40], eyes[40], photo[40];

  userid[0] = head[0] = expression[0] = eyes[0] = photo[0] = '\0';

  /*** scan in the image features ***/
  sscanf(NAME(img), "%[^_]_%[^_]_%[^_]_%[^_]_%d.%[^_]",
    userid, head, expression, eyes, &scale, photo);

  char *p=NULL;
  p = strrchr(eyes,'.');
  if(p!=NULL)
  {
	    userid[0] = head[0] = expression[0] = eyes[0] = photo[0] = '\0';

	    sscanf(NAME(img), "%[^_]_%[^_]_%[^_]_%[^.].%[^_]",
    userid, head, expression, eyes, photo);
		scale = 1;
  }

  p = strrchr(userid,'\\');
  if(p!=NULL)
	  p++;
#if 0
  //if (!strcmp(p, "glickman")) {
  if (!strcmp(eyes, "sunglasses")) {
    net->target[1] = TARGET_HIGH;  /* it's me, set target to HIGH */
  } else {
    net->target[1] = TARGET_LOW;   /* not me, set it to LOW */
  }
#endif

#if BPNN_TYPE

  std::string sid = userid;
  //printf("userid -- %s\n", userid);
  std::set<std::string>::iterator iter = usernames.begin();
  int index = 0;
  while (iter != usernames.end()) {
	  if (!sid.compare(*iter))
		  break;
	  ++iter;
	  ++index;
  }
  //  printf("index -- %d\n", index);
  for (int i = 1; i <= BPNN_N_OUT; ++i) {
	  //int bit = index >> (i - 1) & 1;
	  net->target[i] = index >> (i - 1) & 1 ? TARGET_HIGH : TARGET_LOW;
	  //printf("%d", bit);
  }
  //  for (int i = 1; i <= BPNN_N_OUT; ++i) {
  //	  printf("%lf", net->target[i]);
  //  }
  //  exit(1);

#else

  // angry happy neutral sad
  if (!strcmp(expression, "happy")) {
	  net->target[1] = TARGET_HIGH;
	  net->target[2] = TARGET_HIGH;
  }
  else if (!strcmp(expression, "angry")) {
	  net->target[1] = TARGET_HIGH;
	  net->target[2] = TARGET_LOW;
  }
  else if (!strcmp(expression, "neutral")) {
	  net->target[1] = TARGET_LOW;
	  net->target[2] = TARGET_HIGH;
  }
  else if (!strcmp(expression, "sad")) {
	  net->target[1] = TARGET_LOW;
	  net->target[2] = TARGET_LOW;
  }

#endif
}


/***********************************************************************/
/********* You shouldn't need to change any of the code below.   *******/
/***********************************************************************/

void load_input_with_image(IMAGE *img,BPNN *net)
{
  double *units;
  int nr, nc, imgsize, i, j, k;

  nr = ROWS(img);
  nc = COLS(img);
  imgsize = nr * nc;;
  if (imgsize != net->input_n) {
    printf("LOAD_INPUT_WITH_IMAGE: This image has %d pixels,\n", imgsize);
    printf("   but your net has %d input units.  I give up.\n", net->input_n);
    exit (-1);
  }

  units = net->input_units;
  k = 1;
  for (i = 0; i < nr; i++) {
    for (j = 0; j < nc; j++) {
      units[k] = ((double) img_getpixel(img, i, j)) / 255.0;
      k++;
    }
  }
}
