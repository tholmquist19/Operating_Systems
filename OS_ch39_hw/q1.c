#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <string.h>


int main(int argc, char *argv[]){
  struct stat fs;
  const char *path = argv[1];

  if(argc != 2){
   printf("please enter file path");
  }
  if (stat(path, &fs) == -1) {
        perror("Error");
        return 1;
    }
    
  struct tm *mod_time = localtime(&fs.st_mtime);
  char buff[80];
  strftime(buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", mod_time);
  
  printf("File: %s\n", path);
  printf("Size: %ld bytes\n", fs.st_size);
  printf("Blocks: %ld\n", fs.st_blocks);
  printf("Reference link count: %d\n", fs.st_nlink);
  printf("Permissions (octal): %o\n", fs.st_mode & 0777);
  printf("File type: ");
  if (S_ISREG(fs.st_mode)) {
      printf("Regular file\n");
  } else if (S_ISDIR(fs.st_mode)) {
      printf("Directory\n");
  } else if (S_ISLNK(fs.st_mode)) {
      printf("Symbolic link\n");
  } else {
      printf("Other\n");
  }
  printf("Last modified: %s\n", buff);
  printf("---------------------------------\n\n");



  return 0;
}
