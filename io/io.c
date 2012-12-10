/** SimpleUI
 *
 *  @par Copyright:
 *            2012 (c) Nitin Chadha <upcomingnewton@gmail.com>
 *
 *  @author   Nitin Chadha <upcomingnewton@gmail.com>
 *  @par License:
 *            BSD-2-Clause <http://www.opensource.org/licenses/BSD-2-Clause>
 */
#include "io.h"

#include<string.h>
#include<stdio.h>
#include<malloc.h>


char * sReadFileToMem(const char *filename)
{
	char * filetext = 0;
	FILE *fp = 0;
	int size = 0;
	if((fp = fopen(filename,"r")) != 0)
	{
		      /* get size */
		      fseek(fp,0L,SEEK_END);
		      /* read file possibly partitial */
		      size = ftell (fp);
		      rewind(fp);

		      /* allocate memory */
		      filetext = (char *)calloc(sizeof(char),size + 1);

		      /* check and read */
		      if ((fp != 0)
		       && filetext
		       && size)
		      {
		        int s = fread(filetext, sizeof(char), size, fp);

		                /* check again */
		        if (s != size)
		        { size = 0;
		        free(filetext);
		        filetext = 0;
		        }
		      }

	}
	return filetext;
}
