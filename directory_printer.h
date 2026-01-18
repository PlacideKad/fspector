#ifndef DIR_PRINTER
#define DIR_PRINTER

#include <stdio.h>
#include <stdlib.h>

void string_list_sorter(char** filename_list, int size){
  int i=0;
  while(i<size-1){
    int j=i+1;
    while(j<size){
      if(*filename_list[i]>*filename_list[j]){
        char* c=filename_list[i];
        filename_list[i]=filename_list[j];
        filename_list[j]=c;
        i=-1;
        break;
      }
      j++;
    }
    i++;
  }
 
}
void directory_printer(char** filename_list, int len_list){
  string_list_sorter(filename_list,len_list);
  for (int i=0;i<len_list;i++){
    printf("|---> %s\n",filename_list[i]);
  }
}

#endif