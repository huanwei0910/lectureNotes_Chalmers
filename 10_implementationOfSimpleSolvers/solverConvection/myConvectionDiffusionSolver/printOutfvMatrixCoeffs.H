/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | foam-extend: Open Source CFD
   \\    /   O peration     | Version:     3.2
    \\  /    A nd           | Web:         http://www.foam-extend.org
     \\/     M anipulation  | For copyright notice see file Copyright
-------------------------------------------------------------------------------
License
    This file is part of foam-extend.

    foam-extend is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    foam-extend is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with foam-extend.  If not, see <http://www.gnu.org/licenses/>.


Description
    Print out the coefficients in TEqn for a cell 

SourceFiles
    printOutfvMatrixCoeffs.H

\*---------------------------------------------------------------------------*/


label cellID = 1275;

// Diagonal coeffcients in A
scalarField DD = TEqn.DD();

Info << "diagonal coefficient for a("<< cellID << ","<<  cellID << ") = " << DD[cellID]  << endl;

// source stores the sources coefficients which are directly obtianed from the discretization of the source terms  
scalarField source = TEqn.source();

Info << "source term due to discretization  b("<< cellID << ") = " << source[cellID]  << endl;

// lowerCoeff stores off-diagonal coefficients in the lower triangle of coefficient matrix A
scalarField lowerCoeff = TEqn.lower();

// upperCoeff stores off-diagonal coefficients in the lower triangle of coefficient matrix A
scalarField upperCoeff = TEqn.upper();

// lowerAddr stores the addressing for coefficients in lowerCoeff
labelList lowerAddr = TEqn.lduAddr().lowerAddr();

// upperAddr stores the addressing for coefficients in upperCoeff
labelList upperAddr = TEqn.lduAddr().upperAddr();


Info << "off-diagonal coefficients:" << endl;
// getting access to the off-diagonal coefficients
forAll (lowerAddr,i)
{
    if ( upperAddr[i] == cellID )
    {
	Info << "a("<< cellID << ","<<  lowerAddr[i] << ") : " << lowerCoeff[i] << endl;
    }
    if ( lowerAddr[i] == cellID )
    {
	Info << "a("<< cellID << ","<<  upperAddr[i] << ") : " <<  upperCoeff[i] << endl;
    }
}

