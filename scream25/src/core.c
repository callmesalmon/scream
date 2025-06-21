/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright (c) 2025 Salmon                                                 *
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

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include <scream/core.h>

int* tape;
int size = 3000;
int ascii = 1;
int debug = 0;
int cur = 0;
int len;
int loop = 0;
int break_point = -1;
int comp = 0;
char* dest;
char* con;

int isNumeric(char* str)
{
    for (int i=0;str[i]!=0 && str[i]!='\n';i++)
    {
        if (str[i]=='O' && i==0)
            continue;
        if (str[i]>'9' || str[i]<'0')
        {
            return 0;
        }
    }
    return 1;
}

int fileExists(char* fn)
{
    struct stat buffer;
    return !stat(fn,&buffer);
}

int fileSize(char* fn)
{
    FILE* f = fopen(fn,"r");
    fseek(f,0,SEEK_END);
    int l = ftell(f);
    fclose(f);
    return l;
}

void execute()
{
    int count = 0;
    char buffer[100];
    int break_started = 0;
    for (int i=0;i<len;i++)
    {
        if (i==break_point)
        {
            break_started = 1;
            printf("Break point reached\nEnter s to stop execution, c to continue after break point, e to end break point, otherwise next\n");
            debug = 1;
        }
        if (break_started)
        {
            fgets(buffer,100,stdin);
            if (strcmp(buffer,"s")==0 || strcmp(buffer,"S")==0 )
            {
                return;
            }
            else if (strcmp(buffer,"c")==0 || strcmp(buffer,"C")==0)
            {
                break_started = 0;
                debug = 0;
            }
            else if (strcmp(buffer,"e")==0 || strcmp(buffer,"E")==0)
            {
                break_started = 0;
                debug = 0;
                break_point = -1;
            }
        }
        char c = con[i];
        switch (c)
        {
        case 'A':
            if (debug)
                printf("Move right from cell %d ",cur);
            if (loop)
                cur = (cur+1)%size;
            else
                cur++;
            if (debug)
                printf("to cell %d\n",cur);
            break;
        case 'E':
            if (debug)
                printf("Move left from cell %d ",cur);
            if (loop)
                cur = (cur-1)%size;
            else
                cur--;
            if (debug)
                printf("to cell %d\n",cur);
            break;
        case 'U':
            if (debug)
                printf("Increment cell %d from %d ",cur,tape[cur]);
            tape[cur]++;
            if (debug)
                printf("to %d\n",tape[cur]);
            break;
        case 'O':
            if (debug)
                printf("Decrement cell %d from %d ",cur,tape[cur]);
            tape[cur]--;
            if (debug)
                printf("to %d\n",tape[cur]);
            break;
        case 'u':
            if (tape[cur])
            {
                if (debug)
                    printf("Enter loop at %d\n",i);
                break;
            }
            if (debug)
                printf("Skip loop from %d ",i);
            count = 1;
            while (count>0 && i<len)
            {
                i++;
                if (con[i]=='u')
                {
                    count++;
                }
                else if (con[i]=='o')
                {
                    count--;
                }
            }
            if (debug)
                printf("to %d\n",i);
            break;
        case 'o':
            if (!tape[cur])
            {
                if (debug)
                    printf("Exit loop at %d\n",i);
                break;
            }
            if (debug)
                printf("Loop jump back from %d ",i);
            count = 1;
            while (count>0 && i>=0)
            {
                i--;
                if (con[i]=='u')
                {
                    count--;
                }
                else if(con[i]=='o')
                {
                    count++;
                }
            }
            if (debug)
                printf("to %d\n",i);
            break;
        case 'e':
            if (ascii)
                printf("%c",tape[cur]);
            else
                printf("%d",tape[cur]);
            break;
        case 'a':
            if (ascii)
            {
                fgets(buffer,100,stdin);
                tape[cur] = buffer[0];
            }
            else
            {
                do
                {
                    fgets(buffer,100,stdin);
                    if (!isNumeric(buffer))
                    {
                        printf("Input an integer\n");
                    }
                }while(!isNumeric(buffer));
                tape[cur] = atoi(buffer);
            }
            break;
        }
    }
}

void compile()
{
    FILE* f = fopen(dest,"w");
    if (f==0)
    {
        printf("Cannot write destination file: %s",dest);
        return;
    }
    fputs("/* C Source File generated by SCREAM25 */\n\n",f);
    fputs("#include<stdio.h>\n",f);
    fputs("#include<stdlib.h>\n\n",f);
    if (!ascii)
    {
        fputs("int isNumeric(char* str){\n",f);
        fputs("for (int i=0;str[i]!=0 && str[i] != \'\\n\';i++){\n",f);
        fputs("if (str[i]=='O' && i==0) continue;\n",f);
        fputs("if (str[i]>'9' || str[i]<'0') return 0;\n",f);
        fputs("}\n",f);
        fputs("return 1;\n",f);
        fputs("}\n\n",f);
    }
    fputs("int main(int argc,char** argv){\n\n",f);
    fprintf(f,"int* arr = (int*) malloc(%d*sizeof(int));\n",size);
    fprintf(f,"for(int i=0;i<%d;arr[i]=0,i++);\n",size);
    fprintf(f,"int i = 0;\n");
    fprintf(f,"char buffer[100];\n\n");

    int count = 0;
    int inside = 0;
    int change = 0;

    for (int i=0;i<len;i++)
    {
        char c = con[i];
        switch(c)
        {
        case 'A':
        case 'E':
            change = 0;
            while(i<len)
            {
                c = con[i];
                if (c=='A')
                    change++;
                else if (c=='E')
                    change--;
                else if (c=='U' || c=='O' || c=='u' || c=='o' || c=='e' || c=='a')
                {
                    i--;
                    break;
                }
                i++;
            }
            if (loop)
            {
                fprintf(f,"i = ( i + %d ) %% %d;",change,size);
            }
            else
            {
                fprintf(f,"i += %d ;",change);
            }
            break;
        case 'U':
        case 'O':
            change = 0;
            while (i<len)
            {
                c = con[i];
                if (c=='U')
                    change++;
                else if (c=='O')
                    change--;
                else if(c=='E' || c=='A' || c=='u' || c=='o' || c=='e' || c=='a')
                {
                    i--;
                    break;
                }
                i++;
            }
            fprintf(f,"arr[ i ] += %d;\n",change);
            break;
        case 'u':
            fprintf(f,"while ( arr[ i ] ) {\n");
            count++;
            break;
        case 'o':
            fprintf(f,"}\n");
            count--;
            if (count<0)
            {
                printf("Error to many 'o' at: %d\n",i);
            }
            break;
        case 'e':
            if (ascii)
            {
                fprintf(f,"printf(\"%%c\", arr[ i ] );\n");
            }
            else
            {
                fprintf(f,"printf(\"%%d\", arr[ i ] );\n");
            }
            break;
        case 'a':
            if (ascii)
            {
                fprintf(f,"fgets(buffer,100,stdin);\n");
                fprintf(f,"arr[ i ] = buffer[0];\n");
            }
            else
            {
                fprintf(f,"do {\n");
                fprintf(f,"fgets(buffer,100,stdin);\n");
                fprintf(f,"if (!isNumeric(buffer)) printf(\"Input an integer\\n\");\n");
                fprintf(f,"} while (!isNumeric(buffer));\n");
                fprintf(f,"arr[ i ] = atoi(buffer);\n");
            }
            break;
        }
    }
    while (count>0)
    {
        fputs("}\n",f);
        count--;
    }
    fputs("printf(\"\\n\");\n",f);
    fputs("\nfree(arr);\n",f);
    fputs("\n}\n",f);
    fclose(f);
}
