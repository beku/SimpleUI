 #ifndef S_GTK_RENDERER_H
    #include <libxml/parser.h>
    #include <libxml/tree.h>
    #include "../../simpleUI.h"
    #include "../../sXforms.h"
    #define S_GTK_RENDERER_H
    #define sGTK_UI_FILE  "xforms/sGtkSampleTest6.glade"
    #define sGTK_GLADE_MAIN_WINDOW_NAME "sGTK_GLADE_MAIN_WINDOW_NAME"
    #define GTK_WINDOW_HEIGHT "360"
    #define GTK_WINDOW_WIDTH "480"
    
	typedef int  (*sGtkUIHandlers) (
		sXformsNode * head,
		xmlNode *par
		);
	
	struct sGtkUIHandlers_data{
	  char *type;
	  char *name;
	  char *attrname;
	  char *attrvalue;
	  int strict; // if 1 , then it means it cannot be used a generic handler
	  sGtkUIHandlers        handler;
	};
    
    //functions defined in sGtkParseTree.c
    void sGenerateGladeFile(sXformsNode *head);
	int sGtkGenerateUIFromTree(sXformsNode * head, xmlNode *par);
	int gtk_f_TabsHandler(sXformsNode *head,xmlNode *node);
	int gtk_f_RangeHandler(sXformsNode *head,xmlNode *node);
	int gtk_f_FrameHandler(sXformsNode *head,xmlNode *node);
	int gtk_f_ButtonHandler(sXformsNode *head,xmlNode *node);
	int gtk_f_LabelHandler(sXformsNode *head,xmlNode *node);
	int gtk_f_InputHandler(sXformsNode *head,xmlNode *node);
	int gtk_f_CheckBoxList(sXformsNode *head,xmlNode *node);
	int gtk_f_RadioButtonList(sXformsNode *head,xmlNode *node);
	int gtk_f_Select1Handler(sXformsNode *head,xmlNode *node);
	int gtk_f_TabsHandler(sXformsNode *head,xmlNode *node);
	int gtk_f_MakeRadioButtonGroup(sXformsNode *head,xmlNode *node);
	int gtk_f_MakeListStoreForDropDown(sXformsNode *head,xmlNode *node);
	

    
    // functions defined in sGtkRenderer_Helper.c
    xmlNode * CreateXmlNode(xmlNsPtr ns, char * name);
    xmlNode *CreateXmlNodeWithParent(xmlNode *par,char *name);
    xmlAttr * CreateNodeAttribute(xmlNode *node, char *attrName, char *attrValue);
    xmlNode * Create1ChildNode(xmlNode *par,char *type, char *internal_child);
    xmlNode * Create1ChildNodeWithPlaceholder(xmlNode *par,char *type, char *internal_child);
    xmlNode * Create1SignalNode(xmlNode *par,char *name, char *handler, char *after, char *swapped, char *object, char *last_modification_time);
    void CreatePropertyNodes(xmlNode *par,char **prop_name,char **translatable, char **comments, char **context, char **value, int num_prop);
    xmlNode *Create1PropertyNode(xmlNode *par,char *prop_name,char *translatable, char *comments, char *context, char *value);
    xmlNode *Create1ObjectNode(xmlNode *par,char *id, char *classname,char *constructor, char *type_func);
    xmlNode *CreatePackingNodeWithProperties(xmlNode *par,char **prop_name,char **translatable, char **comments, char **context, char **value, int num_prop);
    xmlNode *CreateDataRow(xmlNode *row,char *id, char *translatable,char *val);
    
    int CalculatePosition(sXformsNode *head);
    xmlNode *MakeHBoxForElements(sXformsNode *head,xmlNode *node);
    void PackElements( xmlNode *par,char *fill, char *expand, int pos);
    void MakeLabel(sXformsNode *head,xmlNode *hbox);
    void MakeRadioButton(sXformsNode *head, xmlNode *par,char *groupname, char *handlername, char *label, int pos);
    void MakeChildButton(sXformsNode *head, xmlNode *par, char *handlername, char *label, int pos);
#endif

