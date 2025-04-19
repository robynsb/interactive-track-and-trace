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
			in
			{
        packages.default = pkgs.stdenv.mkDerivation {
          name = "ParticleTrackTrace"; 
          src = ./.;
          nativeBuildInputs = [ pkgs.cmake pkgs.vtk pkgs.netcdf netcdfcxx4 pkgs.sfml ];
          buildInputs = [ ];
          installPhase = ''
            cp -r "$name.app" $out
          '';
        };
			}
		);
}