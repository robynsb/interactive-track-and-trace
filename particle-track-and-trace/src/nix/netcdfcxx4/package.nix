{
  lib,
  stdenv,
  fetchFromGitHub,
  netcdf,
  hdf5,
  curl,
  cmake,
  ninja
}:
stdenv.mkDerivation rec {
  pname = "netcdf-cxx4";
  version = "4.3.1";

  src = fetchFromGitHub {
    owner = "Unidata";
    repo = "netcdf-cxx4";
    rev = "v${version}";
    sha256 = "sha256-GZ6n7dW3l8Kqrk2Xp2mxRTUWWQj0XEd2LDTG9EtrfhY=";
  };

  patches = [
    ./cmake-h5free.patch
  ];

  preConfigure = ''
    cmakeFlags+="-Dabs_top_srcdir=$(readlink -f ./)"
  '';

  nativeBuildInputs = [
    cmake
    ninja
  ];
  buildInputs = [
    netcdf
    hdf5
    curl
  ];

  doCheck = true;
  enableParallelChecking = false;
  preCheck = ''
    export HDF5_PLUGIN_PATH=${netcdf}/lib/hdf5-plugins
  '';
}
