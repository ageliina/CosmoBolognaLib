# ==========================================================================
# Example code: how to compute the theoretical size function of cosmic voids
# ==========================================================================

# import the CosmoBolognaLib #
import CosmoBolognaLib as cbl 

# set the CosmoBolognaLib and the current directories
cbl.SetDirs("../../../", "./")

# define a cosmological model, using default parameters #
cosm = cbl.Cosmology()

# effective void radius at which the size function is computed
R = 10.

# redshift 
z = 0.

# linear underdensity threshold
del_v = cosm.deltav_L()

# linear overdensity threshold
del_c = cosm.deltac(0.) 

# size function
sf = cosm.size_function(R, z, del_v, del_c, "SvdW")

print 'the size function at R =', R, 'Mpc/h and at z =', z,'is', '%.e' % sf, '(h/Mpc)^3'

