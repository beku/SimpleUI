#include "../sGtk.h"
#include "sGtkCallbacks.h"
#include "../../misc/misc.h"
#include <string.h>
#include <gtk/gtk.h>

char * getGtkWidgetValue(char *type, GtkWidget *widget)
{
	if(!strcmp(type,"GtkEntry")) return  sGetValueOfTextBox(widget);
	else if(!strcmp(type,"GtkComboBox")) return  sGetValueOfComboBox(widget);
	else if(!strcmp(type,"GtkRadioButton")) return  sGetValueOfRadioButton(widget);
	else if(!strcmp(type,"GtkCheckButton")) return  sGetValueOfCheckButton(widget);
	else if(!strcmp(type,"GtkRange")) return  getRangeValue(widget);
	else if(!strcmp(type,"GtkScale")) return  getRangeValue(widget);
	else return (char *)0;
}

char * sGetValueOfTextBox(GtkWidget *widget)
{
	GtkEntry *entry = (GtkEntry *)widget;
	const char *text = gtk_entry_get_text(entry);
	fprintf(stdout," [%s] value is %s\n",__func__,text);
	return s_dupstr(text);
}

char * sGetValueOfComboBox(GtkWidget *widget)
{
	GtkComboBox *combobox = GTK_COMBO_BOX(widget);
	// get the value of the combo box seleted part
	//int p = gtk_combo_box_get_active( combobox );
	const char * txt = gtk_combo_box_get_active_id( combobox );
	//fprintf(stdout," [%s] value is [currently selected index] %d\n",__func__,p);
	fprintf(stdout," [%s] value is [currently selected index] %s\n",__func__,txt);
	return s_dupstr("text");
}

char * sGetValueOfRadioButton(GtkWidget *widget)
{
	// find the group, and then selected radio button
	GSList *temp = gtk_radio_button_get_group((GtkRadioButton *)(widget));
	GtkToggleButton *radio_btn;
	while( temp )
	{
		radio_btn = (GtkToggleButton *)temp->data;
		if ((gtk_toggle_button_get_active (radio_btn)) == TRUE )
		{
			// get the widget's details'
			const char *text = gtk_button_get_label((GtkButton *)radio_btn);
			fprintf(stdout," [%s] value is %s\n",__func__,text);
			return s_dupstr(text);
		}
		temp = temp->next;
	}
	return "null";
}

char * sGetValueOfCheckButton(GtkWidget *widget)
{
	// find the value
	GtkToggleButton *chk_btn = (GtkToggleButton *)widget;
	const char *text = gtk_button_get_label((GtkButton *)chk_btn);
	if((gtk_toggle_button_get_active (chk_btn)) == TRUE )
	{
		fprintf(stdout," [%s] %s is checked\n",__func__,text);
		return "TRUE";
	}
	else
	{
		fprintf(stdout," [%s] %s is not checked\n",__func__,text);
		return "FALSE";	
	}
}

char * getRangeValue(GtkWidget * widget)
{
	GtkRange *range = (GtkRange *)widget;
	gdouble value = gtk_range_get_value(range);
	char buf[5];
	sprintf(buf,"%.1f",value);
	fprintf(stdout," [%s] value is %s\n",__func__,buf);
	return s_dupstr(buf);
}
