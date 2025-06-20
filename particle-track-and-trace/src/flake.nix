{
  description = "Flake for building WaddenZee-Vogel";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-24.11";

		flake-utils.url = "github:numtide/flake-utils"; 
  };

  outputs = { self, nixpkgs, flake-utils }:
		flake-utils.lib.eachDefaultSystem (system: 
			let 
				pkgs = nixpkgs.legacyPackages.${system};
        netcdfcxx4 = pkgs.callPackage ./nix/netcdfcxx4/package.nix { };


        vtkWithGeovis = (pkgs.callPackage (import ./nix/vtk/generic.nix {
          majorVersion = "9.3";
          minorVersion = "1";
          sourceSha256 = "sha256-g1TsCE6g0tw9I9vkJDgjxL/CcDgtDOjWWJOf1QBhyrg=";
        }) {
          qtdeclarative = pkgs.qtdeclarative;
          qttools = pkgs.qttools;
          qtx11extras = pkgs.qtx11extras;
        });
			in
			{
        packages.default = pkgs.stdenv.mkDerivation {
          name = "ParticleTrackTrace"; 
          src = ./.;
          nativeBuildInputs = [ pkgs.cmake vtkWithGeovis pkgs.netcdf netcdfcxx4 pkgs.sfml ];
          buildInputs = [ ];
          installPhase = ''
            cp -r "$name.app" $out
          '';
        };
			}
		);
}