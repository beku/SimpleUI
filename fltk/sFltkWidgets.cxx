#include "sFltk.h"
#include "../simpleUI.h"
#include "../sXforms.h"
	#include <FL/Fl.H>
	#include <FL/Fl_Button.H>
	#include <FL/Fl_Double_Window.H>
	#include <FL/Fl_Pack.H>
	#include <FL/Fl_Scroll.H>
	#include <FL/Fl_Text_Display.H>
	#include <FL/Fl_Help_View.H>
	#include <FL/Fl_Choice.H>
	#include <FL/Fl_Input.H>

struct sFltkUIHandler_s fltk_handlers[] = {
	{
		(char *)"xf:select1",
  		(char *)"xf-select1-handler",
  		(sFltkUIHandler_f)sFltkUIHandler_f_Select1Handler
	},
	{
		(char *)"xf:input",
  		(char *)"xf-input",
  		(sFltkUIHandler_f)sFltkUIHandler_f_InputHandler
	},
	{
		(char *)0,
  		(char *)0,
  		(sFltkUIHandler_f)0
	}
};

void test_widgets(){
	Fl_Group *parent = Fl_Group::current();
	if(!parent){
		fprintf(stdout,"could not find parent");
	}
	else{
		fprintf(stdout,"declared");
		
		Fl_Choice  *f = new Fl_Choice(parent->x(),parent->y(),parent->w(),30,"choice");
		f->add("one");
		f->add("two");
		f->add("three");
	}
}


int sGenerateUIFromTree(sXformsNode * head)
{
	//fprintf(stdout,"\n === PRINTING NODE TREE ===");
	static int y = 0;
	int x = 0,
	    //y = 0,
	    w = 0,
	    h = 0;
	    Fl_Group *parent = Fl_Group::current();
	    x = parent->x();
	    //y = parent->y();
	    w = parent->w();
	    h = 10;
	if( head == 0 ){
		fprintf(stdout,"\n Head node passed is null");
		return 1;
	}
	else{
		sXformsNode *temp ;
		for( temp = head->child;(( temp != 0 ) ) ; temp=temp->next){
			// process this node
			// find corresponding handler 
			if( temp->meta_info && !strcmp(temp->meta_info,"1")){
				continue;
			}
			x = 0;
			while(fltk_handlers[x].type != 0){
				if( !strcmp(temp->type,fltk_handlers[x].type)){
					//found 
					fprintf(stdout,"\n ******* found ***********\n");
					fprintf(stdout,"\n calling handler %d",fltk_handlers[x].handler(temp,x,y,w,h));
					temp->meta_info = (char *)"1"; // node visited
					y = y + 30;
					break;
				}
				x++;
			}
			fprintf(stdout,"\n\t %s : %s",temp->type,temp->name);
			//sPrintsXformsNode(temp);
			if( temp->child == 0){
				fprintf(stdout,"\t\t-- NO CHILD ---\n");
			}else{
				fprintf(stdout,"\n\t------------- chilren -------------\n");
				sGenerateUIFromTree(temp);
				fprintf(stdout,"\n\t------------- chilren end -------------\n");
			}
		}
	}
}

int sFltkUIHandler_f_Select1Handler(sXformsNode *head,int x, int y, int w, int h){
	fprintf(stdout,"janemann , called this function , lol\n");
	//test_widgets();
	return 0;
}

int sFltkUIHandler_f_InputHandler(sXformsNode *head,int x, int y, int w, int h){
	Fl_Group *parent = Fl_Group::current();
	if(!parent){
		fprintf(stdout,"could not find parent");
	}
	else{
		fprintf(stdout,"declared");
		
		Fl_Input  *f = new Fl_Input(parent->x(),y + V_SPACING,parent->w(),90,head->name);
	}
}



