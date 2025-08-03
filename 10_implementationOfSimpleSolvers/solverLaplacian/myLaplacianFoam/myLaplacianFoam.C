/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2025 AUTHOR,AFFILIATION
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Application
    myLaplacianFoam

Description

\*---------------------------------------------------------------------------*/

#include "fvCFD.H" // Include the class declarations
#include "simpleControl.H" // Prepare to read the SIMPLE sub-dictionary
int main(int argc, char *argv[])
{
# include "setRootCase.H" // Set the correct path
# include "createTime.H" // Create the time
# include "createMesh.H" // Create the mesh
simpleControl simple(mesh); // Read the SIMPLE sub-dictionary
# include "createFields.H" // Temperature field T and diffusivity DT
while (simple.loop())
{ while (simple.correctNonOrthogonal())
{
solve( fvm::ddt(T) - fvm::laplacian(DT, T) ); // Solve eq.
}
// # include "write.H" // Write out results at specified time instances}
}
return 0; // End with 'ok' signal
}

// ************************************************************************* //
