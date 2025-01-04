/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright (c) 2025 Elis Staaf                                             *
 *                                                                           *
 * Licensed under the Apache License, Version 2.0 (the "License");           *
 * you may not use this file except in compliance with the License.          *
 * You may obtain a copy of the License at                                   *
 *                                                                           *
 *     http://www.apache.org/licenses/LICENSE-2.0                            *
 *                                                                           *
 * Unless required by applicable law or agreed to in writing, software       *
 * distributed under the License is distributed on an "AS IS" BASIS,         *
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  *
 * See the License for the specific language governing permissions and       *
 * limitations under the License.                                            *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* Standard libraries */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

/* Scream library. */
#include <scream/core.h>

/* Externs */
extern int debug;
extern int comp;
extern char *dest;
extern int *tape;
extern int len;
extern char *con;
extern int size;

int main(int argc,char** argv) {
    char* source = "";
    for (int i=1;i<argc;i++) {
        if (strcmp(argv[i],"-c")==0 || strcmp(argv[i],"-C")==0) {
            comp = 1;
            i++;
            if (i>=argc) {
                printf("No compilation destination provided\n");
                return -5;
            }
            dest = argv[i];
        }
        else if (strcmp(argv[i],"-d")==0 || strcmp(argv[i],"-D")==0) {
            debug = 1;
        }
        else if(strcmp(argv[i],"-h")==0 || strcmp(argv[i],"-H")==0 || strcmp(argv[i],"-?")==0) {
            printf("Scream interpreter: AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
            printf("Usage: %s <source> [options]\n",argv[0]);
            printf("Options:\n");
            printf("-c <dest>\tCompile to C as dest file\n");
            printf("-h\t\tSee Help\n");
            return 0;
        }
        else
        {
            source = argv[i];
        }
    }
    if (strcmp(source,"")==0)
    {
        printf("No source file provided\n");
        return -1;
    }
    if (debug)
        printf("Source: %s\n",source);
    if (!fileExists(source))
    {
        printf("File not accessible: %s\n",source);
        return -2;
    }
    tape = (int*) malloc(size*sizeof(int));
    for (int i=0;i<size;i++)
    {
        tape[i] = 0;
    }
    len = fileSize(source);
    con = (char*) malloc(len*sizeof(char));
    FILE* f = fopen(source,"r");
    for (int i=0;i<len;i++)
    {
        con[i] = fgetc(f);
    }
    fclose(f);
    if (comp)
    {
        compile();
    }
    else
    {
        execute();
        printf("\n");
    }
    free(tape);
}
