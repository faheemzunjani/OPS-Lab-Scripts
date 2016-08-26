#include <stdio.h>

int main(void)
{
   FILE *fp;
   char filename[80];
   long length;

   printf("Input file name:");
   scanf("%s",filename);
   fp = fopen(filename,"rb");

   if(fp==NULL) {
      printf("File not found!\n");
   }
   else {
      fseek(fp,0L,SEEK_END);
      length=ftell(fp);
      printf("The file's length is %1ld Bytes.\n",length);
      fclose(fp);
   }

   return 0;
}