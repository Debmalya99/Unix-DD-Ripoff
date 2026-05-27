/*
ccdd: This is a program that tries to replicate the unix/linux
dd command in a well, rather dumb way. I did it as I was subscribed to the
Coding Challenge Newsletter and it was published on 23rd May, 2026
Here's the Link to that: https://codingchallenges.substack.com/p/coding-challenge-121-dd?utm_source=post-email-title&publication_id=1483213&post_id=198937038&utm_campaign=email-post-title&isFreemail=true&r=30yi93&triedRedirect=true&utm_medium=email

Usage:
This is just a dumb file-copier that has the following usage
ccdd ifile=<Name of the input file> ofile=<Name of the output file> bs=<Size of the blocks in which the data will be copied>


Date Written: 27th May 2026
Author: Debmalya Mitra
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// reg.functions

// doc: Takes a string in the format key=value and returns the key and value as 2 seperate strings.
char** get_key_value_pair(char* a_str)
{
  char* ref_str = (char*)malloc(sizeof(char) * 100);
  strcpy(ref_str,a_str);
  char* key = ref_str;
  char* value = NULL;
  int i = 0;
  for(i = 0;*(ref_str + i) != '=';i++)
  {
    // Just bloody increment it, nothing to actually do
  }
  value = ref_str + i + 1; // Now it points to after the equal
  *(ref_str + i) = '\0'; // Instead of the equal we just have a string end, this signals the end of the source.
  char** return_pair = malloc(sizeof(char*) * 2);
  *return_pair = key;
  *(return_pair + 1) = value;

  return return_pair;
}

void process_file_copy(char* input_file_name,char* output_file_name,unsigned int buffer_size)
{
  char* BUFFER = malloc(buffer_size * sizeof(char)); // All I know is that "char" ensures that it is of 1 byte.
  FILE* fp_src = fopen(input_file_name,"rb");
  FILE* fp_dest = fopen(output_file_name,"wb");
  unsigned int bytes_read;
  int full_blocks = 0;
  int partial_blocks = 0;
  unsigned int total_bytes = 0;

  if (fp_src && fp_dest) // i.e we could open both properly
  {
    while((bytes_read = fread(BUFFER,1,sizeof(BUFFER),fp_src)) > 0)
    {
      total_bytes += bytes_read;
      if (bytes_read == sizeof(BUFFER)) full_blocks += 1;
      else partial_blocks += 1;

      
      fwrite(BUFFER, 1, sizeof(BUFFER),fp_dest);
    }
    printf("%d+%d record in\n",full_blocks,partial_blocks);
    printf("%d+%d record out\n",full_blocks,partial_blocks);
    printf("%d bytes copied\n",total_bytes);
  }
  else{
    printf("Error in opening the source or the destination file. ;(");
  }
}

// reg.main
int main(int argc, char** argv)
{
  char* ifile_name;
  char* ofile_name;
  unsigned int block_size;
  if ((argc == 1 )||(strcmp(*(argv + 1),"-h") == 0) || (strcmp(*(argv + 1),"--help") == 0))
  {
      printf("Usage: \n");
      printf("ccdd ifile=<Name of the input file> ofile=<Name of the output file> bs=<Block size for copy as integer>\n");
      exit(0);
  }
  for(int i = 1;i<argc;i++)
  {
    char* raw_arg = *(argv+i);
    char** kv_p = get_key_value_pair(raw_arg);
    char* key = *kv_p;
    char* value = *(kv_p + 1);

    if (strcmp(key,"ifile") == 0)
    {
      ifile_name = value;
    }

    else if(strcmp(key,"ofile") == 0)
    {
      ofile_name = value;
    }

    else if (strcmp(key,"bs") == 0)
    {
      block_size = atoi(value);
    }

    else{
      printf("Error! Arguments not provided properly\n");
      printf("Usage: \n");

      printf("ccdd ifile=<Name of the input file> ofile=<Name of the output file> bs=<Block size for copy as integer>\n");
    }
  }

  //region.main.copyfile
  process_file_copy(ifile_name,ofile_name,block_size);

  
  return 0;
}
