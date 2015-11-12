/*******************************************************************
 *  Copyright (C) 2010 by Federico Marulli                         *
 *  federico.marulli3@unibo.it                                     *
 *                                                                 *
 *  This program is free software; you can redistribute it and/or  *
 *  modify it under the terms of the GNU General Public License as *
 *  published by the Free Software Foundation; either version 2 of *
 *  the License, or (at your option) any later version.            *
 *                                                                 *
 *  This program is distributed in the hope that it will be useful,*
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  *
 *  GNU General Public License for more details.                   *
 *                                                                 *
 *  You should have received a copy of the GNU General Public      *
 *  License along with this program; if not, write to the Free     *
 *  Software Foundation, Inc.,                                     *
 *  59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.      *
 *******************************************************************/

/**
 *  @file GlobalFunc/FuncCosmology.cpp
 *
 *  @brief Generic functions that use the class Cosmology
 *
 *  This file contains the implementation of a set of generic
 *  functions that use the class Cosmology
 *
 *  @author Federico Marulli 
 *
 *  @author federico.marulli3@unbo.it
 */

#include "GlobalFunc.h"
using namespace cosmobl;


// ============================================================================


void cosmobl::Vmax_DC_distribution (vector<double> &dc, vector<double> &nObj, vector<double> D_C, vector<double> zobj_min, vector<double> zobj_max, double &z_min, double &z_max, double &zbin_min, double &zbin_max, Cosmology &cosm, double &Area, int &nObjRan, int &idum, bool norm, string file_Vmax, double delta_dc_Vmax)
{
  if (dc.size()>0 || nObj.size()>0) ErrorMsg("Error in Vmax_DC_distribution of GlobalFunc_Cosmology.cpp)!");

  Ran ran(idum);

  vector<double> dc_Vmax, ww;
  double Volume, zz;

  for (unsigned int i=0; i<D_C.size(); i++) { 
    for (int j=0; j<nObjRan; j++) {
      Volume = ran.doub()*cosm.Volume(zobj_min[i],zobj_max[i],Area);
      zz = cosm.max_redshift(Volume, Area, zobj_min[i]);
      if (z_min<zz && zz<z_max) { 
	dc_Vmax.push_back(cosm.D_C(zz));
	ww.push_back(1.);
      }
    }
  }

  double fact = (norm) ? double(dc_Vmax.size())/double(D_C.size()) : dc_Vmax.size();
  
  double dc1 = cosm.D_C(zbin_min), dc2 = cosm.D_C(zbin_max);

  int nbin = nint((dc2-dc1))/delta_dc_Vmax;

  bool linear = 1;
  
  distribution(dc, nObj, dc_Vmax, ww, nbin, linear, file_Vmax, fact, dc1, dc2);
}


// ============================================================================================


double cosmobl::AP_shift_r (double &redshift, Cosmology &cosm1, Cosmology &cosm2)
{
  return cosm2.D_V(redshift)/cosm1.D_V(redshift);
}

double cosmobl::AP_shift_rp (double &redshift, Cosmology &cosm1, Cosmology &cosm2)
{
  return cosm1.D_A(redshift)/cosm2.D_A(redshift);
}

double cosmobl::AP_shift_pi (double &redshift, Cosmology &cosm1, Cosmology &cosm2)
{
  return cosm2.HH(redshift)/cosm1.HH(redshift);
}


// ============================================================================================


void cosmobl::max_separations_AP (double &Rp_max, double &Pi_max, double &redshift, Cosmology &cosm1, vector<Cosmology> &cosm2, double *rpM_AP, double *piM_AP, double *rM_AP) 
{
  vector<double> _rp(cosm2.size()), _pi(cosm2.size());

  for (unsigned int i=0; i<cosm2.size(); i++) {
    _rp[i] = Rp_max*AP_shift_rp(redshift,cosm1,cosm2[i]);
    _pi[i] = Pi_max*AP_shift_pi(redshift,cosm1,cosm2[i]);
  }

  *rpM_AP = Max(_rp);
  *piM_AP = Max(_pi);
  *rM_AP = sqrt(pow(*rpM_AP,2)+pow(*piM_AP,2));
}


// ============================================================================================


double cosmobl::converted_xi (double &RR, double &redshift, vector<double> rr, vector<double> Xi, Cosmology &cosm1, Cosmology &cosm2, bool direction) 
{
  if (RR==0) ErrorMsg("Error in converted_xi of GlobalFuncCosmology.cpp! RR must be >0!");

  double gamma = AP_shift_r (redshift, cosm1, cosm2);

  // direction: 0:cosm2->cosm1, 1:cosm1->cosm2
  double lgRR = (direction) ? log10(RR/gamma) : log10(RR*gamma);

  vector<double> lgrr, lgXi;
  for (unsigned int i=0; i<rr.size(); i++) 
    if (rr[i]>0 && Xi[i]>0) {
      lgrr.push_back(log10(rr[i]));
      lgXi.push_back(log10(Xi[i]));
    }

  return pow(10., interpolated(lgRR, lgrr, lgXi, "Poly", 4));
}


// ============================================================================


double cosmobl::converted_xi (double &RP, double &PI, double &redshift, vector<double> rp, vector<double> pi, vector< vector<double> > Xi, Cosmology &cosm1, Cosmology &cosm2, bool direction) 
{
  double fDA = AP_shift_rp(redshift, cosm1, cosm2);
  double fH = AP_shift_pi(redshift, cosm1, cosm2);
  
  // direction: 0:cosm2->cosm1, 1:cosm1->cosm2
  double _RP = (direction) ? RP*fDA : RP/fDA;
  double _PI = (direction) ? PI*fH : PI/fH;

  return interpolated_2D(_RP, _PI, rp, pi, Xi, "Poly", 4);
}
