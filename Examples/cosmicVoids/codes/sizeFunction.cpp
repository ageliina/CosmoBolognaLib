// ==========================================================================
// Example code: how to compute the theoretical size function of cosmic voids
// ==========================================================================

#include "Cosmology.h"
 
// these two variables contain the name of the CosmoBolognaLib
// directory and the name of the current directory (useful when
// launching the code on remote systems)
std::string cbl::par::DirCosmo = DIRCOSMO, cbl::par::DirLoc = DIRL;
 
 
int main () {

  try {
   
    // -----------------------------------------------
    // ----- use default cosmological parameters ----- 
    // -----------------------------------------------
    
    cbl::cosmology::Cosmology cosm;


    // -------------------------------------------------------------
    // ----- compute the Sheth & van de Weygaert size function -----
    // -------------------------------------------------------------

    double RR = 10.; // effective void radius at which the size function is computed
    double redshift = 0.;
    
    double del_v = cosm.deltav_L(); // linear underdensity threshold
    double del_c = cosm.deltac(0.); // linear overdensity threshold
    
    std::cout << cosm.size_function(RR, redshift, del_v, del_c, "SvdW") << std::endl;
   
  }
  
  catch (cbl::glob::Exception &exc) { std::cerr << exc.what() << std::endl; exit(1); }
   
  return 0;
}
