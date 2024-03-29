/* ----------------------------------------------------------------------
   LAMMPS - Large-scale Atomic/Molecular Massively Parallel Simulator
   http://lammps.sandia.gov, Sandia National Labo0ratories
   Steve Plimpton, sjplimp@sandia.gov

   Copyright (2003) Sandia Corporation.  Under the terms of Contract
   DE-AC04-94AL85000 with Sandia Corporation, the U.S. Government retains
   certain rights in this software.  This software is distributed under 
   the GNU General Public License.

   See the README file in the top-level LAMMPS directory.
------------------------------------------------------------------------- */

#ifdef COMPUTE_CLASS

ComputeStyle(spec/atom,ComputeSpecAtom)

#else

#ifndef LMP_COMPUTE_SPEC_ATOM_H
#define LMP_COMPUTE_SPEC_ATOM_H

#include "compute.h"
#include "pointers.h"

namespace LAMMPS_NS {

class ComputeSpecAtom : public Compute {
 public:
  ComputeSpecAtom(class LAMMPS *, int, char **);
  ~ComputeSpecAtom();
  void init() {}
  void compute_peratom();
  double memory_usage();

 private:
  int nvalues;
  int nmax;
  double *vector;
  double **array;
  double *buf;
  double *vbuf;       

  typedef void (ComputeSpecAtom::*FnPtrPack)(int);
  FnPtrPack *pack_choice;    

  void pack_q(int);
  void pack_x(int);
  void pack_y(int);
  void pack_z(int);
  void pack_vx(int);
  void pack_vy(int);
  void pack_vz(int);

  void pack_jid01(int);
  void pack_jid02(int);
  void pack_jid03(int);
  void pack_jid04(int);
  void pack_jid05(int);
  void pack_jid06(int);
  void pack_jid07(int);
  void pack_jid08(int);
  void pack_jid09(int);
  void pack_jid10(int);
  void pack_jid11(int);
  void pack_jid12(int);

  void pack_abo01(int);
  void pack_abo02(int);
  void pack_abo03(int);
  void pack_abo04(int);
  void pack_abo05(int);
  void pack_abo06(int);
  void pack_abo07(int);
  void pack_abo08(int);
  void pack_abo09(int);
  void pack_abo10(int);
  void pack_abo11(int);
  void pack_abo12(int);

  class PairReaxC *reaxc;
  struct _reax_system  	*system;
  struct _reax_atom  	*my_atoms;
};

}

#endif
#endif

/* ERROR/WARNING messages:

E: Illegal ... command

Self-explanatory.  Check the input script syntax and compare to the
documentation for the command.  You can use -echo screen as a
command-line option when running LAMMPS to see the offending line.

E: Compute reaxc/atom for atom reaxc that isn't allocated

Self-explanatory.

E: Invalid keyword in compute reaxc/atom command

Self-explanatory.

*/
