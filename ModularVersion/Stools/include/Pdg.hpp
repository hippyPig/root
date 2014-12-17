#ifndef SCPH_CONSTANTS_PDG_NAMESPACE_H
#define SCPH_CONSTANTS_PDG_NAMESPACE_H

namespace pdg
{
  // Masses
  // Leptons
  const double e   =    0.511;
  const double mu  =  105.658;
  const double tau = 1776.82;

  // Light
  const double pi0 =  134.977;
  const double pi  =  139.570;
  const double phi = 1019.455;

  // Strange
  const double k0 = 497.614;
  const double k  = 493.677;
  const double k1 = 1272.0;

  // Charmed
  const double d0 = 1864.86;
  const double d  = 1869.62;
  const double ds = 1968.49;

  // Bottom
  const double b0 = 5279.58;
  const double b  = 5279.25;
  const double bs = 5366.77;

  // Lamdbas
  const double lambda = 1115.68;
  const double lc = 2286.46;
  const double lb = 5619.4;

  // ccbar
  const double jpsi = 3096.916;
  const double psi2 = 3686.109;
  const double psi2s = 3686.109;

  const double p = 938.272046;

  const double rho = 775.49;

  // PDG IDs
  namespace id {
    // Leptons
    const int e   = 11;
    const int mu  = 13;
    const int tau = 15;

    // Light
    const int pi0 = 111;
    const int pi  = 211;
    const int phi = 333;

    // Strange
    const int k0 = 311;
    const int k  = 321;
    const int kstr  = 323;
    const int kstr0 = 313;

    // Charmed
    const int d0 = 421;
    const int d  = 411;
    const int ds = 431;

    // Bottom
    const int b0 = 511;
    const int b  = 521;
    const int bs = 531;

    // ccbar
    const int jpsi =    443;
    const int psi2 = 100443;
  }
}

#endif
