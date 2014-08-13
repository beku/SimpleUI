 #ifndef S_GTK_RENDERER_H
   //#include "../sQtCallbacks/sQt_Cb.h"
    #include <libxml/parser.h>
    #include <libxml/tree.h>
    #include "../../sCallbackData/sCallbackData.h"
    #include "../../simpleUI.h"
    #include "../../sXforms.h"
    #define S_QT_RENDERER_H
    #define sQT_UI_FILE  "sQt.ui"
    #define sQT_CLOSE_BUTTON  "BtnDone_Main"
    #define sQT_MAIN_WINDOW_NAME "sQT_MAIN_WINDOW_NAME"
    #define QT_WINDOW_HEIGHT "681"
    #define QT_WINDOW_WIDTH "458"
    
	typedef int  (*sQtUIHandlers) (
		sXformsNode * head,
		xmlNode *par,
		struct sCbData  **CallBackData,
		xmlDoc *modelPtr,
		CallBackInterfaceFunction func 
		);
	
	struct sQtUIHandlers_data{
	  char *type;
	  char *name;
	  char *attrname;
	  char *attrvalue;
	  int strict; // if 1 , then it means it cannot be used a generic handler
	  sQtUIHandlers        handler;
	};
    
    //functions defined in sGtkParseTree.c
struct sCbData * sQtGenerateGladeFile(sXformsNode *head,xmlDoc *modelPtr,CallBackInterfaceFunction func );
int sQtGenerateUIFromTree(sXformsNode * head, xmlNode *par,struct sCbData **CallBackData, xmlDoc *modelPtr,CallBackInterfaceFunction func );
int kde_f_TabsHandler(sXformsNode *head,xmlNode *node,struct sCbData **CallBackData, xmlDoc *modelPtr,CallBackInterfaceFunction func );
int kde_f_FrameHandler(sXformsNode *head,xmlNode *node,struct sCbData **CallBackData, xmlDoc *modelPtr,CallBackInterfaceFunction func );
int kde_f_LabelHandler(sXformsNode *head,xmlNode *node,struct sCbData **CallBackData, xmlDoc *modelPtr,CallBackInterfaceFunction func );
int kde_f_ButtonHandler(sXformsNode *head,xmlNode *node,struct sCbData **CallBackData, xmlDoc *modelPtr,CallBackInterfaceFunction func );
int kde_f_InputHandler(sXformsNode *head,xmlNode *node,struct sCbData **CallBackData, xmlDoc *modelPtr,CallBackInterfaceFunction func );
int kde_f_Select1Handler(sXformsNode *head,xmlNode *node,struct sCbData **CallBackData, xmlDoc *modelPtr,CallBackInterfaceFunction func );
int kde_f_RadioButtonList(sXformsNode *head,xmlNode *node,struct sCbData **CallBackData, xmlDoc *modelPtr,CallBackInterfaceFunction func );
int kde_f_CheckBoxList(sXformsNode *head,xmlNode *node,struct sCbData **CallBackData, xmlDoc *modelPtr,CallBackInterfaceFunction func );
int kde_f_RangeHandler(sXformsNode *head,xmlNode *node,struct sCbData **CallBackData, xmlDoc *modelPtr,CallBackInterfaceFunction func );
	

    
    // functions defined in sQtRenderer_Helper.c
xmlNode *Create1ObjectNode(xmlNode *par,char *nodename, char *value);
xmlNode *CreateNodeText(xmlNode* par,char *val);
xmlAttr * CreateNodeAttribute(xmlNode *node, const char *attrName, const char *attrValue);
xmlNode *Create1WidgetNode(xmlNode *par,char *name, char *classname,char **prop_name, char **prop_type, char **value, int num_prop);
xmlNode *Create1PropertyNode(xmlNode *par,char *prop_name,char *prop_type, char *value);
void CreatePropertyNodes(xmlNode *par,char **prop_name, char **prop_type, char **value, int num_prop);
xmlNode *Create1GeometryProp(xmlNode *par,char *x, char *y, char *width, char *height);
xmlNode *Create1WidgetNodeWithStringProp(xmlNode *par,char *name, char *classname,char *propname, char *strval);
xmlNode *CreateStringProperty(xmlNode *par,char *propname, char *strval );
xmlNode *CreateLayout(xmlNode *par,char *classname, char *name );
xmlNode *CreateFrame(xmlNode *par,char *classname, char *name );
xmlNode *CreateSpacer(xmlNode *par,char *spacerName, char *orientation, char *width, char *height, const char * row, const char * column );
xmlNode *CreateItemNode(xmlNode *par,xmlNode *child, const char * row, const char * column);
xmlNode * CreateXmlNode(xmlNsPtr ns, char * name);
xmlNode *CreateStringAttribute(xmlNode *par, char *strval );
#endif

