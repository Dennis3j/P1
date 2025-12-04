// --------------------------------------------------------------------
//
// main.cpp
//
// Base file for input and memory storage for P0.
//
// CS5130 Advanced Algorithms
//
//
// ---------------------------------------------------------------------

#include "defs.h"
#include "added.h"   // added: my 2-medians routine lives here; I call it once to get the low-cluster size

int main(int argc, char ** argv) 
{
  // process command line arguments
  if (argc != 2)
    fatal("Usage:\n\n   P1 inputFileName  (input file contains a list of numbers)\n\n");

  timer t;
  // start timer; if QUIET=1 (grading), dont print the message
  if (!QUIET) t.start("Timer started."); else t.start();

  char *inputFileName = argv[1];  
  FILE *inputFile;
  char tempStrng [STRING_LENGTH]; // string for temporary storage
  float *numbers;                 // will point to array holding input numbers
  int numCount = 0;               // cardinality of input numbers
  
  if (!QUIET) {
    std::cout << "\nCommand line arguments: \n\t";
    for (int i = 0; i < argc; i++)
      std::cout << argv[i] << " ";
    std::cout << "\n\n";
    std::cout << "Input will be read from '" << inputFileName << "'.\n";

   std::cout << "Numbers will be optimally clustered using 2-medians.\n";
   std::cout << "Program will output the optimal 2-medians solution value,\n";
   std::cout << "followed by the cardinality of the cluster containing the smallest value.\n\n";
  }
    
  // make sure input file can be opened, error otherwise
  if ((inputFile = fopen(inputFileName, "r")) == NULL)
    fatal("Unable to open input file.");
   
  // pass 1: scan to count how many values are in the file
  while (!feof(inputFile)) {  
    fscanf(inputFile, "%s", tempStrng); 
    if (!feof(inputFile))
      numCount++;
  }  
  
  if (!QUIET)
    std::cout << numCount << " values in input file.\n";
    
  // allocate the numbers array based on the count we just computed
  if ((numbers = new float[numCount]) == NULL)
    fatal("memory not allocated");
    
  // pass 2: rewind and actually read the numbers into the array
  rewind(inputFile);
  for (int i = 0; i < numCount; i++) {  
    fscanf(inputFile, "%s", tempStrng);
    numbers[i] = atof(tempStrng); // convert string to float and store in array    
  }
  fclose(inputFile);
  
  if (VERBOSE) {
    std::cout << "\nValues given in input file:\n";
    for (int i = 0; i < numCount; i++)
      std::cout << numbers[i] << "\n";
    std::cout << "\n\n";
  }
  
  // guard: need at least 2 values to form 2 clusters
  if (numCount < 2)
    fatal("Not enough data (need at least 2 values).");

  //Call the functuion that gives me the full 2-medians solution
  //this is going to return the best cost, the medians, and k
  // compute full optimal 2-medians solution (O(n log n))
  TwoMediansSolution sol = computeTwoMediansSolution(numbers, numCount);

  // Program output requirements for P1:
  // 1) optimal 2-medians solution value
  // 2) cardinality of cluster containing the smallest value
  std::cout << "Optimal 2-medians solution value: " << sol.totalCost << std::endl;
  std::cout << "Cardinality of low cluster: " << sol.k << std::endl;

  // cleanup the buffer I allocated
  delete[] numbers;

  // stop timer; if QUIET=1, do it silently
  if (!QUIET) t.stop("\nTimer stopped."); else t.stop();

  // print a friendly elapsed time only when not quiet
  if (!QUIET) {
    double compTime = t.timeVal();
    int seconds = (int)compTime % 60;
    int min = (int)compTime / 60;
    int hour = min / 60;
    min = min % 60;
    std::cout << hour << " hours, " << min << " minutes, " << seconds << " seconds.\n" << std::endl;
  }

  return 0;
}

