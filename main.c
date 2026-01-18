#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>

int main(int argc, char* argv[]){
  char* file_path;

  if(argc > 1){
    file_path=argv[1];
    struct stat file_infos;
    char* command_result;
    if(stat(file_path,&file_infos)==0){
      int permissions=file_infos.st_mode & 0777;
      struct group* grp=getgrgid(file_infos.st_gid);
      struct passwd* pwd=getpwuid(file_infos.st_uid);
      printf("group: %s\n",grp->gr_name);
      printf("user : %s\n",pwd->pw_name);
      printf("%o\n",permissions);
      printf("%ldB\n",file_infos.st_size);
      if(S_ISREG(file_infos.st_mode)){
        struct stat link_infos;
        if(lstat(file_path,&link_infos)==0){
          if(S_ISLNK(link_infos.st_mode)){
            printf("l\n");
            printf("%o\n",link_infos.st_mode&0777);
          }
          else{
            printf("f\n");
          }
        }
      }else if(S_ISDIR(file_infos.st_mode)){
        printf("d\n");
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