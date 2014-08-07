#include <QApplication>
#include "sKDE.h"
#include "sKdeCallbacks/sKde_Cb.h"
#include "sKdeRenderers/sKdeRenderer.h"
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <string.h>
#include "../simpleUI.h"
#include "../sXforms.h"
#include "../xml/sXml.h"
#include "../io/io.h"
#include "../sCallbackData/sCallbackData.h"
#include "../sXforms.h"

void usage(int argc, char ** argv)
{
	fprintf(stdout,"\nUsage:\n%s -i xforms.xhtml [-o result]\n", argv[0]);
}

#if defined(LIBXML_TREE_ENABLED) && defined(LIBXML_OUTPUT_ENABLED)
int main ( int argc , char **argv )
{
	fprintf(stdout,"\n===== SIMPLE UI TOOLKIT =====\n\n");
	 const char *wrong_arg = 0;
	 char *output_xml_file = 0;
	 char *xforms_text = 0;
	 char *input_xml_file = 0;
	 sXformsNode *head;
	 struct sCbData *CallBackData;
	 xmlDoc *modelDocPtr;
    struct qt_cb_data *cb_data = (struct qt_cb_data *)0;
	if(argc)
	{
		#define OY_PARSE_STRING_ARG( opt ) \
                        if( pos + 1 < argc && argv[pos][i+1] == 0 ) \
                        { opt = argv[pos+1]; \
                          if( opt == 0 && strcmp(argv[pos+1],"0") ) \
                            wrong_arg = "-" #opt; \
                          ++pos; \
                          i = 1000; \
                        } else if(argv[pos][i+1] == '=') \
                        { opt = &argv[pos][i+2]; \
                          if( opt == 0 && strcmp(&argv[pos][i+2],"0") ) \
                            wrong_arg = "-" #opt; \
                          i = 1000; \
                        } else wrong_arg = "-" #opt; \
                        
                        
  	if(argc != 1)
  	{
    		int pos = 1, i;
    		while(pos < argc)
    		{
      			switch(argv[pos][0])
      			{
			case '-':
			    for(i = 1; i < (int)strlen(argv[pos]); ++i)
			    switch (argv[pos][i])
			    {
			      case 'o': OY_PARSE_STRING_ARG( output_xml_file ); break;
			      case 'i': OY_PARSE_STRING_ARG( input_xml_file ); break;
			      case 'v': break;//oy_debug += 1; break;
			      case 'h': usage(argc, argv);
				        exit (0); break;
			      case 'l': /* only for compatibility with cmd line */ break;
#if 0
			      case '-':
				        if(strcmp(&argv[pos][2],"verbose") == 0)
				        { 
						//oy_debug += 1; 
						i=100; 
						break;
				        }
				        STRING_ADD( t, &argv[pos][2] );
				        text = oyStrrchr_(t, '=');
				        /* get the key only */
				        if(text)
				          text[0] = 0;
				        oyStringListAddStaticString_( &other_args,&other_args_n,
				                                      t,
				                            oyAllocateFunc_,oyDeAllocateFunc_ );
				        if(text)
				        oyStringListAddStaticString_( &other_args,&other_args_n,
				                            oyStrrchr_(&argv[pos][2], '=') + 1,
				                            oyAllocateFunc_,oyDeAllocateFunc_ );
				        else {
				          if(argv[pos+1])
				          {
				            oyStringListAddStaticString_( &other_args,
				                                          &other_args_n,
				                                          argv[pos+1],
				                            oyAllocateFunc_,oyDeAllocateFunc_ );
				            ++pos;
				          } else wrong_arg = argv[pos];
				        }
				        if(t) oyDeAllocateFunc_( t );
				        t = 0;
				        i=100; 
					break;
#endif
			      case '?':
			      default:
				        fprintf(stderr, "%s -%c\n", ("Unknown argument"), argv[pos][i]);
				        usage(argc, argv);
				        exit (0);
				        break;
			    }
            		break;
        		default:
           		wrong_arg = argv[pos];
	      		}
			if( wrong_arg )
			{
				fprintf(stderr, "%s %s\n", ("wrong argument to option:"), wrong_arg);
				exit(1);
			}
	     		++pos;
    		}

  	}
  	}
	


fprintf(stdout,"INPUT FILE = %s\n",input_xml_file);

  if(!input_xml_file)
  {
#if 0
    size_t text_size = 0;
    text = oyReadStdinToMem_(&text_size, oyAllocateFunc_);

    if(text_size == 0)
    {
                        usage(argc, argv);
                        exit (0);
    }
#else
  usage(argc, argv);
  exit (0);
#endif
  }


  
  if(input_xml_file)
  {
   xforms_text =  sReadFileToMem(input_xml_file);
   //fprintf(stdout,"output xml file is : %s \n\n",xforms_text);
  }
  head = ParseXformsToTree( xforms_text,&modelDocPtr);
  //sPrintsXformsTree(head);


  CallBackData = sKdeGenerateGladeFile(head,modelDocPtr,&DummyIfFunction);
  print_user_data(CallBackData);
      QApplication a(argc, argv);
    SimpleUiKde w(CallBackData);
    w.show();
    a.exec();
   
  
if(output_xml_file)
  {
      FILE *fp = fopen(output_xml_file,"w");
      if( fp != NULL )
      xmlDocDump(fp, modelDocPtr);
      fclose(fp);
  }
  xmlDocDump(stdout, modelDocPtr);
    fprintf(stdout,"\n");
    fprintf(stdout,"\n");
 return 0;
}
#else
    int main(int argc, char **argv)
    {
        fprintf(stderr,"\n ERROR. LIB-XML IS NOT PROPERLY COMPILED");
        exit(1);
    }
#endif
