#ifndef _ARGCGECK_H_
#define _ARGCGECK_H_


int CHECK(int argc, char**argv, int *arg_data);

void PRINT_HELP();

int CHECK_ARGS(int argc, char**argv,int*arg_data);

int CHECK_INPUT_FILE(char*arg_input);

int CHECK_OUTPUT_CATALOG(char*arg_output);

#endif