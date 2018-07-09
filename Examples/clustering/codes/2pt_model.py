# =====================================================================================
# Example code: how to compute power spectrum and two-point correlation function models
# =====================================================================================


### import Python modules for scientific computing and plotting ###

import numpy as np

print "I'm importing matplotlib..."
import matplotlib.pyplot as plt


### import the CosmoBolognaLib ###

import CosmoBolognaLib as cbl


# set the CosmoBolognaLib and the current directories

cbl.SetDirs("../../../", "./")


### create an object of class Cosmology ###

cosmo = cbl.Cosmology(cbl.CosmologicalModel__Planck15_)


### define k and r for the computation of dark matter power spectrum and  two point correlation correlation function ###

kk = np.logspace(-3, 0, 100)
rr = np.linspace(1., 100, 50)


### Compute the power spectrum using CAMB  ###

PkCAMB = np.asarray([cosmo.Pk(kk[i], "CAMB", False, 0.2) for i in range(len(kk))])


### Compute the two point correlation function using CAMB ###

xiCAMB = [cosmo.xi_DM(rr[i], "CAMB", 0.2, "test", False) for i in range(len(rr))]


### Plot the results ###

plt.figure(1)
plt.loglog(kk, PkCAMB, label="CAMB linear")
plt.xlabel(r"$k$")
plt.ylabel(r"$P(k)$")
plt.legend(loc="upper right")
plt.show(block=False)

plt.figure(2)
plt.xlabel(r"$r \, \, [\mathrm{Mpc} h^{-1}]$")
plt.ylabel(r"$\xi(r)$")
plt.loglog(rr, xiCAMB, label="CAMB linear")
plt.legend(loc="upper right")
plt.show(block=False)
