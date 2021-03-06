with import <nixpkgs> {};
with builtins;

stdenv.mkDerivation {
  name = "env";
  buildInputs = [
    pkgconfig
    openssl
    cmake
    gcc
    gnuplot
    valgrind

    liquid-dsp
    hackrf
    inspectrum

    octave
  ];

  shellHook = "
  ";

}
