#include <gtk/gtk.h>
#include "../sGtk.h"
#include "sGtkCallbacks.h"
#include "../../misc/misc.h"
#include "../../sCallbackData/sCallbackData.h"

gboolean 
on_window_destroy  (GtkWidget *widget,GdkEvent  *event, gpointer   user_data) 
{
	//fprintf(stdout," destroy event called\n");
	struct sCbData *data = (struct sCbData *)user_data;
	UpdateModel(data);
    gtk_main_quit ();
  return 0;
}

void CallBackFunction(GtkWidget *widget,gpointer Data)
{
  struct sCbData *data = (struct sCbData *)Data;
  struct sCbData *temp;
  struct sCbData *temp2;
  char *widgetname = s_dupstr((char *)gtk_buildable_get_name (GTK_BUILDABLE (widget)));
  printf(" ==============================================\n");
  printf(" CALLBACK RECEIVED FROM %s\n",widgetname);
  for(temp = data; temp ;temp = temp->next )
  {
    if (!strcmp(temp->name,widgetname))
    {
      GtkWidget *par = gtk_widget_get_toplevel( widget);
      char *value = getGtkWidgetValue(temp->meta_info,widget);
      if( strcmp(temp->ref,"0")  && strcmp(temp->init_val,"READONLY")){ 
        UpdateModelandCallUserFunction(temp->ref,value,data);
        // UPDATE UI
      }
      if(temp->nextref){
			 temp2 = temp->nextref;
				while(temp2 != 0)
				{
				    GtkWidget *present_widget = (GtkWidget *)0;
				    SearchWidget(par,temp2->name,&present_widget);
		        if( present_widget != (GtkWidget *)0)
		        {
			        char *newvalue2 = getGtkWidgetValue(temp2->meta_info,present_widget);
			        if( strcmp(temp2->ref,"0") && strcmp(temp2->init_val,"READONLY")){
                  UpdateModelandCallUserFunction(temp2->ref,newvalue2,data);
              }
		        }
					temp2 = temp2->next;
				}
			}
			UpdateUI(data,par); 
			break;
		}
  }
}

void on_Range_value_changed(GtkRange *range,gpointer user_data){
  /*struct gtk_cb_data *head = (struct gtk_cb_data *)user_data;*/
  //print_user_data(head);
  char *rangename = s_dupstr((char *)gtk_buildable_get_name (GTK_BUILDABLE (range)));
  //printf(" NAME OF RANGE Is %s\n", rangename);
  struct gtk_cb_data *rangedata = (struct gtk_cb_data*)get_pointer_to_user_data_by_name(rangename,user_data);
  if( rangedata== (struct gtk_cb_data *)0)
	{
		fprintf(stdout," NO CORRESPONDING USER DATA\n");
	}
	else
	{
		getGtkWidgetValue("GtkRange",GTK_WIDGET(range));
		
		// find all ref and update their values
		/*
		if(togglebutton_data->nextref){
			GtkWidget *par = gtk_widget_get_toplevel( (GtkWidget *)togglebutton_name); //gtk_widget_get_parent
			if(gtk_widget_is_toplevel(par))
			{
				struct gtk_cb_data *temp2 = togglebutton_data->nextref;
				while(temp2 != 0)
				{
					GtkWidget *present_widget = (GtkWidget *)0;
					SearchWidget(par,temp2->name,&present_widget);
					if( present_widget != (GtkWidget *)0)
					{
						// get it's value
						getGtkWidgetValue(temp2->meta_info,present_widget);
					}
					temp2 = temp2->next;
				}
			}
		}
		*/
	}
	
}

void on_btn_clicked(GtkButton *btn , gpointer user_data)
{
	/*struct gtk_cb_data *head = (struct gtk_cb_data *)user_data;
	print_user_data(head);*/
	char *btn_name = s_dupstr((char *)gtk_buildable_get_name (GTK_BUILDABLE (btn)));
	// search for this btn_name in user_data
	struct gtk_cb_data *btn_data = (struct gtk_cb_data *)get_pointer_to_user_data_by_name(btn_name,user_data);
	// since this is a button, it would have reference to other widgets
	// find those widgets in the gtk tree and get their values and update corresponding values.
	
	// get the  container
	GtkWidget *par = gtk_widget_get_toplevel( (GtkWidget *)btn); //gtk_widget_get_parent
	//GtkWidget *par = gtk_widget_get_parent( (GtkWidget *)btn);
	if(gtk_widget_is_toplevel(par))
	{
		//fprintf(stdout," par-name is : %s\n",gtk_buildable_get_name (GTK_BUILDABLE (par)));
	}
	
	// find all ref and update their values
	struct gtk_cb_data *temp2 = btn_data->nextref;
	while(temp2 != 0)
	{
		GtkWidget *present_widget = (GtkWidget *)0;
		SearchWidget(par,temp2->name,&present_widget);
		if( present_widget != (GtkWidget *)0)
		{
			// get it's value
			getGtkWidgetValue(temp2->meta_info,present_widget);
		}
		temp2 = temp2->next;
	}
	//fprintf(stdout," Button clicked %s\n", gtk_buildable_get_name (GTK_BUILDABLE (btn)));
	/*GtkWidgetPath *  gpath =    gtk_widget_get_path (GTK_WIDGET(btn));
	char * g_path_str  = gtk_widget_path_to_string (gpath);
	fprintf(stdout," path is : %s\n",g_path_str);*/
	
}

void on_combobox_changed(GtkComboBox *widget, gpointer user_data)
{
	/*struct gtk_cb_data *head = (struct gtk_cb_data *)user_data;
	print_user_data(head);*/
	char *combo_box_name = s_dupstr((char *)gtk_buildable_get_name (GTK_BUILDABLE (widget)));
	//fprintf(stdout," NAME OF COMBO BOX IS %s\n",combo_box_name);
	// search for this btn_name in user_data
	struct gtk_cb_data *combo_box_data = (struct gtk_cb_data *)get_pointer_to_user_data_by_name(combo_box_name,user_data);
	// since this is a combo box, it won't have much references, 
	// find  widgets in the gtk tree and get their values and update corresponding values.
	if( combo_box_data == (struct gtk_cb_data *)0)
	{
		fprintf(stdout," NO CORRESPONDING USER DATA\n");	
	}
	else
	{
		
		getGtkWidgetValue(combo_box_data->meta_info,GTK_WIDGET(widget));
		
		// find all ref and update their values
		if(combo_box_data->nextref){
			GtkWidget *par = gtk_widget_get_toplevel( (GtkWidget *)combo_box_name); //gtk_widget_get_parent
			if(gtk_widget_is_toplevel(par))
			{
				struct gtk_cb_data *temp2 = combo_box_data->nextref;
				while(temp2 != 0)
				{
					GtkWidget *present_widget = (GtkWidget *)0;
					SearchWidget(par,temp2->name,&present_widget);
					if( present_widget != (GtkWidget *)0)
					{
						// get it's value
						getGtkWidgetValue(temp2->meta_info,present_widget);
					}
					temp2 = temp2->next;
				}
			}
		}
	}
}


void on_radiobutton_toggled(GtkToggleButton *togglebutton,gpointer user_data)
{
	/*struct gtk_cb_data *head = (struct gtk_cb_data *)user_data;
	print_user_data(head);*/
	char *togglebutton_name = s_dupstr((char *)gtk_buildable_get_name (GTK_BUILDABLE (togglebutton)));
	fprintf(stdout," NAME OF RADIO BUTTON IS %s\n",togglebutton_name);
	// search for this btn_name in user_data
	struct gtk_cb_data *togglebutton_data = (struct gtk_cb_data *)get_pointer_to_user_data_by_name(togglebutton_name,user_data);
	// since this is a combo box, it won't have much references, 
	// find  widgets in the gtk tree and get their values and update corresponding values.
	if( togglebutton_data == (struct gtk_cb_data *)0)
	{
		fprintf(stdout," NO CORRESPONDING USER DATA\n");	
	}
	else
	{
		getGtkWidgetValue(togglebutton_data->meta_info, GTK_WIDGET(togglebutton));
		
		// find all ref and update their values
		if(togglebutton_data->nextref){
			GtkWidget *par = gtk_widget_get_toplevel( (GtkWidget *)togglebutton_name); //gtk_widget_get_parent
			if(gtk_widget_is_toplevel(par))
			{
				struct gtk_cb_data *temp2 = togglebutton_data->nextref;
				while(temp2 != 0)
				{
					GtkWidget *present_widget = (GtkWidget *)0;
					SearchWidget(par,temp2->name,&present_widget);
					if( present_widget != (GtkWidget *)0)
					{
						// get it's value
						getGtkWidgetValue(temp2->meta_info,present_widget);
					}
					temp2 = temp2->next;
				}
			}
		}
	}
}

void on_checkbutton_toggled(GtkToggleButton *togglebutton,gpointer user_data)
{
	/*struct gtk_cb_data *head = (struct gtk_cb_data *)user_data;
	print_user_data(head);*/
	char *togglebutton_name = s_dupstr((char *)gtk_buildable_get_name (GTK_BUILDABLE (togglebutton)));
	fprintf(stdout," NAME OF CHECK BUTTON IS %s\n",togglebutton_name);
	// search for this btn_name in user_data
	struct gtk_cb_data *togglebutton_data = (struct gtk_cb_data *)get_pointer_to_user_data_by_name(togglebutton_name,user_data);
	// since this is a combo box, it won't have much references, 
	// find  widgets in the gtk tree and get their values and update corresponding values.
	if( togglebutton_data == (struct gtk_cb_data *)0)
	{
		fprintf(stdout," NO CORRESPONDING USER DATA\n");	
	}
	else
	{
		getGtkWidgetValue(togglebutton_data->meta_info,GTK_WIDGET(togglebutton));
		
		// find all ref and update their values
		if(togglebutton_data->nextref){
			GtkWidget *par = gtk_widget_get_toplevel( (GtkWidget *)togglebutton_name); //gtk_widget_get_parent
			if(gtk_widget_is_toplevel(par))
			{
				struct gtk_cb_data *temp2 = togglebutton_data->nextref;
				while(temp2 != 0)
				{
					GtkWidget *present_widget = (GtkWidget *)0;
					SearchWidget(par,temp2->name,&present_widget);
					if( present_widget != (GtkWidget *)0)
					{
						// get it's value
						getGtkWidgetValue(temp2->meta_info,present_widget);
					}
					temp2 = temp2->next;
				}
			}
		}
	}
}

int SearchWidget(GtkWidget *container, char *search_name,GtkWidget **t){
		GtkWidget *temp;
		GList * children = gtk_container_get_children (GTK_CONTAINER(container));
		
		GList *temp3 = children;
		int c = 0;
		//if( GTK_IS_COMBOBOX(container)) return 0;
		while(temp3 != 0)
		{
			c++;
			temp3 = temp3->next;
		}
		////fprintf(stdout,"\t\t ============== %d ===================== \n",c);
		while(children != 0)
		{
			////fprintf(stdout,"\t =========**===== %d ===================== \n",strlen(gtk_buildable_get_name(GTK_BUILDABLE(children->data))));
			temp = children->data; //(GtkWidget *)
			
			////fprintf(stdout,"\t\t == children name == %s,%d\n",gtk_buildable_get_name(GTK_BUILDABLE(temp)));
			if(gtk_buildable_get_name(GTK_BUILDABLE(temp)) == NULL) return 0;
			if( !strcmp(search_name,gtk_buildable_get_name(GTK_BUILDABLE(temp))))
			{
				//fprintf(stdout,"\t\t =========== FOUND\n");
				(*t) =  temp;
				return 1;
			}
			if( GTK_IS_CONTAINER(temp) == 1)
			{
				//fprintf(stdout,"\t %% CONTAINER = %s, SEARCH FOR %s\n",gtk_buildable_get_name(GTK_BUILDABLE(temp)),search_name);
				if( SearchWidget(temp,search_name,t) == 1 ){
					return 1;
					//fprintf(stdout,"\t\t =========== FOUND2\n");
				}
			}
			children = children->next;
		}
	//fprintf(stdout," returning 0, container = %s\n",gtk_buildable_get_name(GTK_BUILDABLE(container)));
	return 0;
}

void UpdateUI(struct sCbData *list,GtkWidget *par)
{
    GtkWidget *target = (GtkWidget *)0;
    struct sCbData *temp, *temp2;
    for( temp = list ; temp ; temp =temp->next )
    {
      if( strcmp(temp->ref,"0"))
      {
				    SearchWidget(par,temp->name,&target);
		        if( target != (GtkWidget *)0)
		        {
                UpdateWidgetValue(temp->meta_info,temp->value,target);
		        }
      }
      if( temp->nextref )
      {
          for( temp2 = temp->nextref ; temp2 ; temp2 =temp2->next )
          {
            if( strcmp(temp2->ref,"0"))
            {
				      SearchWidget(par,temp2->name,&target);
		          if( target != (GtkWidget *)0)
		          {
                  UpdateWidgetValue(temp2->meta_info,temp2->value,target);
		          }
            }
          }
      }
    }
}


