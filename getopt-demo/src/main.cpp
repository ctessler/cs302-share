#include<iostream>
#include<getopt.h>
#include<sstream>
using namespace std;

#define VERSION "1.0a"

/*
 * Command line arguments
 *
 * getopt.h provides:
 *   no_argument
 *   required_argument
 *   optional_argument   
 */
const struct option long_opts[] = {
  "version", no_argument,       0, 'v',
  "help",    no_argument,       0, 'h',
  "years",   required_argument, 0, 'y',
  "name",    required_argument, 0, 'n'
};

void dohelp() {
  cout << R"END(
argparse:

A demonstration of accepting command line arguments of distinct types.
Use man 3 getopt_long for more details.

Usage: argparse [OPTIONS] <INPUTFILE>
    -v/--version        Prints the version of the program and exits.
    -h/--help           Prints this message and exits.
    -y/--years <NUMBER> Requires an integer argument.
    -n/--name  <NAME    Requires a string argument.

Examples:
    argparse --help

    argparse -y 42 infile.txt
)END" << endl;
}

int main(int argc, char** argv) {

  /*
   * getopt.h provides optind
   *
   * This is the index of the _next_ argument to be processed
   */

  /* getopt_long returns -1 when no argument remain to be parsed */
  int gl_return = 0;
  /*
   * opt_idx is the index into the long_opts array of the argument
   * being parsed
   */
  int opt_idx = 0;

  int years;
  string name;
  istringstream buffer;
  while (gl_return != -1) {
    gl_return = getopt_long(argc, argv, "vhy:n:",
			    long_opts, &opt_idx);

    switch (gl_return) {
    case 'v': /* version */
      cout << "Version " << VERSION << endl;
      break;

    case 'h': /* help */
      dohelp();
      return(0);

    case 'y': /* years */
      /* getopt.h provides optarg the argument to the current flag */
      buffer.clear();
      buffer.str(optarg);
      buffer >> years;
      break;

    case 'n': /* name */
      buffer.clear();
      buffer.str(optarg);
      buffer >> name;
      break;
    }
  }

  string infilename;
  if (optind < argc) {
    /* Required command line argument */
    buffer.clear();
    buffer.str(argv[optind]);
    buffer >> infilename;
    optind++;
  } else {
    dohelp();
    return(-1);
  }

  cout << "Years: " << years << endl
       << "Name : " << name << endl
       << "File : " << infilename << endl;
  
  return 0;
}
