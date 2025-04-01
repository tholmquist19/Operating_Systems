#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>


int main(int argc, char *argv[]) {
  char cwd[1024];
    
  if (argc < 2 || strcmp(argv[1], "-l") == 0) {
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
      perror("get cwd");
      return 1;
    }
  } if(argc > 2){
    strncpy(cwd, argv[2], sizeof(cwd) - 1);
    cwd[sizeof(cwd) - 1] = '\0'; 
  }if(argc == 2 && strcmp(argv[1], "-l") != 0){
    strncpy(cwd, argv[1], sizeof(cwd) - 1);
    cwd[sizeof(cwd) - 1] = '\0';
  }
  

  DIR *dir = opendir(cwd);
  if (dir == NULL) {
    perror("open directory");
    return 1;
  }

  struct dirent *entry;
  while ((entry = readdir(dir)) != NULL) {
    if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
      printf("\nFile name:  %s\n", entry->d_name);
      
      if(argc>1 && strcmp(argv[1], "-l") == 0){
        char path[2048];
        snprintf(path, sizeof(path), "%s/%s", cwd, entry->d_name);
        
        struct stat fs;
        if (stat(path, &fs) == -1) {
          perror("Error");
          continue;
        }
        
        struct passwd *owner = getpwuid(fs.st_uid);
        struct group *group = getgrgid(fs.st_gid);
        
        printf("Size: %ld bytes\nPermissions (octal): %o\n", fs.st_size, fs.st_mode & 0777);
        printf("Owner: %s\n", owner ? owner->pw_name : "Unknown");
        printf("Group: %s\n", group ? group->gr_name : "Unknown");
      }
    }
  }

  closedir(dir);
  return 0;
}

