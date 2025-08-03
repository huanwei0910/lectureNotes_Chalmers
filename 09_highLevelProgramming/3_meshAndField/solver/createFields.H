volScalarField p
(
IOobject
(
"p",
runTime.timeName(),
mesh,
IOobject::MUST_READ,
IOobject::AUTO_WRITE
),
mesh
);
Info<< p << endl;
Info<< p.boundaryField()[0] << endl;