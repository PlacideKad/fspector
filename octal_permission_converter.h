#ifndef OCTAL_PERMISSION
#define OCTAL_PERMISSION

#include <stdio.h>
#include <stdlib.h>


void formatter (int i,char* input_stream, char* output_stream){
      for (int j=0; j<3;j++){
        output_stream[3*i+j]=input_stream[j];
      }
      if(i==2)
        output_stream[9*sizeof(char)]='\0';
}
char* converter(int decimal_permission){

  int size=4*sizeof(char);
  char *octal_string =malloc(size);
  char *octal_string_formatted=malloc(10*sizeof(char));

  sprintf(octal_string,"%o",decimal_permission);

  int i=0;
  while(octal_string[i]!='\0'){
    switch (octal_string[i])
    {
    case '0':
      formatter(i,"---",octal_string_formatted);
      break;      
    case '1':
      formatter(i,"--x",octal_string_formatted);
      break;
    case '2':
      formatter(i,"-w-",octal_string_formatted);
      break;
    case '3':
      formatter(i,"-wx",octal_string_formatted);
      break;
    case '4':
      formatter(i,"r--",octal_string_formatted);
      break;
    case '5':
      formatter(i,"r-x",octal_string_formatted);
      break;
    case '6':
      formatter(i,"rw-",octal_string_formatted);
      break;
    case '7':
      formatter(i,"rwx",octal_string_formatted);
      break;
    default:
      break;
    }
    i++;
  }
  free(octal_string);
  return octal_string_formatted;
}

#endif