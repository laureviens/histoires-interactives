// CPP code for bad_alloc ; de https://www.geeksforgeeks.org/bad_alloc-in-cpp/
#include <iostream> 
#include <new> 
  
// Driver code 
int main () { 
  try
  { 
     int* gfg_array = new int[10000000000];    //Int�ressant: jouer avec le nombre de int demand�s!
  } 
  catch (std::bad_alloc & ba) 
  { 
     std::cerr << "bad_alloc caught: " << ba.what(); 
  } 
  return 0; 
} 
