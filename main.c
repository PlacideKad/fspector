#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>
#include "octal_permission_converter.h"

int main(int argc, char* argv[]){
  char* file_path;

  if(argc > 1){
    file_path=argv[1];
    struct stat file_infos;

    if(stat(file_path,&file_infos)==0){

      if(S_ISREG(file_infos.st_mode)){

        char file_type_bit='-';
        int permissions=file_infos.st_mode & 0777;
        char* permissions_bits=converter(permissions);
        long int file_size=file_infos.st_size;
        struct group* grp=getgrgid(file_infos.st_gid);
        struct passwd* pwd=getpwuid(file_infos.st_uid);
        struct stat link_infos;

        if(lstat(file_path,&link_infos)==0){

          if(S_ISLNK(link_infos.st_mode)){

            file_type_bit='l';
            permissions=link_infos.st_mode & 0777;
            printf("%d\n",permissions);
            permissions_bits=converter(permissions);
          }
        }
        printf("%c%s %s %s %ldB\n",file_type_bit,permissions_bits,pwd->pw_name,grp->gr_name,file_size);
        free(permissions_bits);
      }else if(S_ISDIR(file_infos.st_mode)){

        struct dirent* entry;
        DIR *dp=opendir(file_path);
        if (dp==NULL){
          perror("Could not open the directory\n");
          return EXIT_FAILURE;
        }

        while((entry=readdir(dp))!=NULL){
          printf("%s\n",entry->d_name);
        }
        closedir(dp);
      }else{
        return EXIT_FAILURE;
      }
    }else{
      printf("Error: fspector: can't find %s\n",file_path);
      return EXIT_FAILURE;
    }
  }else{
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}