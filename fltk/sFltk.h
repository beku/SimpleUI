#ifndef SIMPLE_UI_FLTK_H
#define SIMPLE_UI_FLTK_H
#include "../sXforms.h"

typedef int  (*sFltkUIHandler_f) (
	sXformsNode * head,
	int x, 
	int y,
	int w, 
	int h
);

struct sFltkUIHandler_s {
  char *type;
  char *name;
  sFltkUIHandler_f        handler;
};


#define H_SPACING 10
#define V_SPACING 3
#define ROW_HEIGHT 25
#define BOX_WIDTH 250
#define SELECT_WIDTH 176



int sGenerateUIFromTree(sXformsNode * head);
void test_widgets();


int sFltkUIHandler_f_Select1Handler(sXformsNode *head, int x, int y, int w, int h);
int sFltkUIHandler_f_InputHandler(sXformsNode *head,int x, int y, int w, int h);
#endif
