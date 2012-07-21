#include "../sGtk.h"
#include "sGtkCallbacks.h"
#include "../../misc/misc.h"
#include <malloc.h>

struct gtk_cb_data * AllocateMemoryForGtkCBNode()
{
	struct gtk_cb_data *node = (struct gtk_cb_data *)malloc(sizeof(struct gtk_cb_data ));
	if ((node) == NULL)
	{
		fprintf(stdout,"\n could not allocate memory");
		(node) = (struct gtk_cb_data *)0;
	}
	else
	{
		(node)->ref = (char *)0;
		(node)->init_val= (char *)0;
		(node)->value= (char *)0;
		(node)->name= (char *)0;
		(node)->meta_info= (char *)0;
		(node)->next = (struct gtk_cb_data *)0;
		(node)->prev= (struct gtk_cb_data *)0;
		(node)->nextref = (struct gtk_cb_data *)0;
	}
	return node;
}

struct gtk_cb_data * AppendNode(struct gtk_cb_data **head,char *ref_, char *init_val_,char *value_,char *name_,char *meta_info_){
	/*
	1. allocate memory
	2. adjust the values
	3. adjust pointers
	4. return pointers to this node
	*/
	fprintf(stdout,"\n ==> , head = %s, name = %s, meta = %s",(*head) != 0 ? (*head)->name : "null",name_,meta_info_);
	static int i = -1;
	i++;
	struct gtk_cb_data *newnode = AllocateMemoryForGtkCBNode();
	if( newnode != 0){
		newnode->ref = s_dupstr(ref_);
		newnode->name = s_dupstr(name_);
		newnode->value = s_dupstr(value_);
		newnode->init_val = s_dupstr(init_val_);
		newnode->meta_info = s_dupstr(meta_info_);
		struct gtk_cb_data *temp = (*head);
		if( (*head) == 0){
			// no node in the system
			(*head) = newnode;
		}
		else
		{
			while( temp->next != 0){
				temp = temp->next;
			}
			temp->next = newnode;
			newnode->prev = temp;
		}
	}
	return newnode;
}

struct gtk_cb_data * MakeDummy()
{
	struct gtk_cb_data *head = (struct gtk_cb_data *)0;
	struct gtk_cb_data *btn =  AppendNode(&head,"btn_personal_info", "NULL","NULL","btn_personal_info","xf:trigger");
	struct gtk_cb_data *CheckBtn1 =  AppendNode(&head,"btn_personal_info", "NULL","NULL","checkbutton_newpaper1","GtkCheckButton");
	struct gtk_cb_data *CheckBtn2 =  AppendNode(&head,"btn_personal_info", "NULL","NULL","checkbutton_newpaper3","GtkCheckButton");
	struct gtk_cb_data *CheckBtn3 =  AppendNode(&head,"btn_personal_info", "NULL","NULL","checkbutton_newpaper5","GtkCheckButton");
	struct gtk_cb_data *btn1 =  AppendNode(&btn->nextref,"ref2", "init_val","value","combobox_prefix","GtkComboBox");
	struct gtk_cb_data *btn2 =  AppendNode(&btn->nextref,"ref2", "init_val","value","entry_FirstName","GtkEntry");
	struct gtk_cb_data *btn3 =  AppendNode(&btn->nextref,"ref2", "init_val","value","entry_MiddleName","GtkEntry");
	struct gtk_cb_data *btn31 =  AppendNode(&btn->nextref,"ref2", "init_val","value","entry_LastName","GtkEntry");
	struct gtk_cb_data *btn32 =  AppendNode(&btn->nextref,"ref2", "init_val","value","entry_dob","GtkEntry");//entry_dob
	struct gtk_cb_data *btn33 =  AppendNode(&btn->nextref,"ref2", "init_val","value","radiobutton_nothing","GtkRadioButton");
	struct gtk_cb_data *btn4 =  AppendNode(&head,"combobox_prefix", "init_val","value","combobox_prefix","GtkComboBox");
	
	return head;
}


void print_user_data(struct gtk_cb_data *head)
{
	struct gtk_cb_data *temp = head;
	struct gtk_cb_data *temp2;
	fprintf(stdout,"\n == PRINTING USER DATA == \n");
	while( temp != 0)
	{
		fprintf(stdout,"\n( %s,%s,%s,%s,%s )",temp->ref,temp->init_val,temp->value,temp->name,temp->meta_info);
		temp2 = temp->nextref;
		while( temp2 )
		{
			fprintf(stdout," -> ( %s,%s,%s,%s,%s )",temp2->ref,temp2->init_val,temp2->value,temp2->name,temp2->meta_info);
			temp2 = temp2->next;
		}
		temp = temp->next;
	}
	fprintf(stdout,"\n");
}

struct gtk_cb_data *get_pointer_to_user_data_by_name(const char *_name, struct gtk_cb_data *head)
{
	struct gtk_cb_data *temp = head;
	while(temp!=0)
	{
		if( !(strcmp(_name,temp->name)))
		{
			return temp;
		}
		temp = temp->next;
	}
	return (struct gtk_cb_data *)0;
}

