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
    if(stat(file_path,&file_infos)==0){
      char file_type_bit='-';
      char* permissions_bits;
      int permissions=(int)file_infos.st_mode & 0777;
      long int file_size=file_infos.st_size;
      struct group* grp=getgrgid(file_infos.st_gid);
      struct passwd* pwd=getpwuid(file_infos.st_uid);

      if(S_ISREG(file_infos.st_mode)){
        struct stat link_infos;
        if(lstat(file_path,&link_infos)==0){
          if(S_ISLNK(link_infos.st_mode)){
            file_type_bit='l';
            permissions=(int)link_infos.st_mode & 0777;
          }
        }
      }else if(S_ISDIR(file_infos.st_mode)){
        file_type_bit='d';
      }else{
        return EXIT_FAILURE;
      }
      printf("%c%o \t %s \t %s \t %ldB\n",file_type_bit,permissions,pwd->pw_name,grp->gr_name,file_size);
    }else{
      printf("Error: fspector: can't find %s\n",file_path);
      return EXIT_FAILURE;
    }
  }else{
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}