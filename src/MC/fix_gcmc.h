/* ----------------------------------------------------------------------
   LAMMPS - Large-scale Atomic/Molecular Massively Parallel Simulator
   http://lammps.sandia.gov, Sandia National Laboratories
   Steve Plimpton, sjplimp@sandia.gov

   Copyright (2003) Sandia Corporation.  Under the terms of Contract
   DE-AC04-94AL85000 with Sandia Corporation, the U.S. Government retains
   certain rights in this software.  This software is distributed under
   the GNU General Public License.

   See the README file in the top-level LAMMPS directory.
------------------------------------------------------------------------- */

#ifdef FIX_CLASS

FixStyle(gcmc,FixGCMC)

#else

#ifndef LMP_FIX_GCMC_H
#define LMP_FIX_GCMC_H

#include "stdio.h"
#include "fix.h"

namespace LAMMPS_NS {

class FixGCMC : public Fix {
 public:
  FixGCMC(class LAMMPS *, int, char **);
  ~FixGCMC();
  int setmask();
  void init();
  void pre_exchange();
  void attempt_atomic_translation();
  void attempt_atomic_deletion();
  void attempt_atomic_insertion();
  void attempt_molecule_translation();
  void attempt_molecule_rotation();
  void attempt_molecule_deletion();
  void attempt_molecule_insertion();
  double energy(int, int, int, double *);
  int pick_random_gas_atom();
  int pick_random_gas_atom_in_region();
  int pick_random_gas_molecule();
  int pick_random_gas_molecule_in_region();
  double molecule_energy(int);
  void get_rotation_matrix(double, double *);
  void get_model_molecule();
  void update_gas_atoms_list();
  double compute_vector(int);
  double memory_usage();
  void write_restart(FILE *);
  void restart(char *);

 private:
  int rotation_group,rotation_groupbit;
  int rotation_inversegroupbit;
  int ngcmc_type,nevery,seed;
  int ncycles,nexchanges,nmcmoves;
  int ngas;                 // # of gas atoms on all procs
  int ngas_local;           // # of gas atoms on this proc
  int ngas_before;          // # of gas atoms on procs < this proc
  int molflag;              // 0 = atomic, 1 = molecular system
  int regionflag;           // 0 = anywhere in box, 1 = specific region
  int iregion;              // GCMC region
  char *idregion;           // GCMC region id

  int maxmol;               // largest molecule tag across all existing atoms
  int natoms_per_molecule;  // number of atoms in each gas molecule

  double ntranslation_attempts;
  double ntranslation_successes;
  double nrotation_attempts;
  double nrotation_successes;
  double ndeletion_attempts;
  double ndeletion_successes;
  double ninsertion_attempts;
  double ninsertion_successes;

  int gcmc_nmax;
  int max_region_attempts;
  double gas_mass;
  double reservoir_temperature;
  double chemical_potential;
  double displace;
  double max_rotation_angle;
  double beta,zz,sigma,volume;
  double xlo,xhi,ylo,yhi,zlo,zhi;
  double region_xlo,region_xhi,region_ylo,region_yhi,region_zlo,region_zhi;
  double region_volume;
  double *sublo,*subhi;
  int *local_gas_list;
  double **cutsq;
  double **atom_coord;
  double *model_atom_buf;
  tagint imagetmp;

  class Pair *pair;

  class RanPark *random_equal;
  class RanPark *random_unequal;
  
  class Atom *model_atom;

  void options(int, char **);
};

}

#endif
#endif

/* ERROR/WARNING messages:

E: Illegal ... command

Self-explanatory.  Check the input script syntax and compare to the
documentation for the command.  You can use -echo screen as a
command-line option when running LAMMPS to see the offending line.

E: Fix GCMC region does not support a bounding box

UNDOCUMENTED

E: Fix GCMC region cannot be dynamic

UNDOCUMENTED

E: Fix GCMC region extends outside simulation box

UNDOCUMENTED

E: Region ID for fix GCMC does not exist

UNDOCUMENTED

E: Invalid atom type in fix GCMC command

The atom type specified in the GCMC command does not exist.

E: Fix GCMC cannot exchange individual atoms belonging to a molecule

This is an error since you should not delete only one atom of a molecule.
The user has specified atomic (non-molecular) gas exchanges, but an atom
belonging to a molecule could be deleted.

E: All mol IDs should be set for fix GCMC group atoms

The molecule flag is on, yet not all molecule ids in the fix group have
been set to non-zero positive values by the user. This is an error since
all atoms in the fix GCMC group are eligible for deletion, rotation, and
translation and therefore must have valid molecule ids.

E: Fix GCMC molecule command requires that atoms have molecule attributes

Should not choose the GCMC molecule feature if no molecules are being
simulated. The general molecule flag is off, but GCMC's molecule flag
is on.

E: Fix GCMC incompatible with given pair_style

Some pair_styles do not provide single-atom energies, which are needed
by fix GCMC.

E: Cannot use fix GCMC in a 2d simulation

Fix GCMC is set up to run in 3d only. No 2d simulations with fix GCMC
are allowed.

E: Cannot use fix GCMC with a triclinic box

Fix GCMC is set up to run with othogonal boxes only. Simulations with
triclinic boxes and fix GCMC are not allowed.

E: Could not find fix group ID

UNDOCUMENTED

E: Illegal fix GCMC gas mass <= 0

The computed mass of the designated gas molecule or atom type was less 
than or equal to zero.

E: Cannot do GCMC on atoms in atom_modify first group

This is a restriction due to the way atoms are organized in a list to
enable the atom_modify first command.

E: Fix GCMC ran out of available molecule IDs

This is a code limitation where more than MAXSMALLINT (usually around
two billion) molecules have been created. The code needs to be 
modified to either allow molecule ID recycling or use bigger ints for
molecule IDs. A work-around is to run shorter simulations.

E: Fix GCMC could not find any atoms in the user-supplied template molecule

When using the molecule option with fix GCMC, the user must supply a 
template molecule in the usual LAMMPS data file with its molecule id
specified in the fix GCMC command as the "type" of the exchanged gas.

E: Fix GCMC incorrect number of atoms per molecule

The number of atoms in each gas molecule was not computed correctly.

U: Fix GCMC fix group should be all

Fix GCMC will ignore the fix group specified by the user. User should
set the fix group to "all". Fix GCMC will overwrite the user-specified
fix group with a group consisting of all GCMC gas atoms.

U: Fix GCMC region does not support a bounding box 
 
Not all regions represent bounded volumes.  You cannot use 
such a region with the fix GCMC command. 
 
E: Fix GCMC region cannot be dynamic 
 
Only static regions can be used with fix GCMC. 
 
E: Fix GCMC region extends outside simulation box 
 
Self-explanatory. 
 
E: Region ID for fix GCMC does not exist 
 
Self-explanatory.



*/
