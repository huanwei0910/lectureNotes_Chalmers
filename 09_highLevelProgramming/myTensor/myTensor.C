#include "tensor.H"
#include "dimensionedTensor.H"
#include "tensorField.H"
using namespace Foam;
int main()
{
tensor T( 11, 12, 13, 21, 22, 23, 31, 32, 33);
Info << "T: " << T << endl;
Info << "Txz: " << T.xz() << endl;

Info << "========================================= " << endl;
tensor t1(1, 2, 3, 4, 5, 6, 7, 8, 9);
tensor t2(1, 2, 3, 1, 2, 3, 1, 2, 3);
tensor t3 = t1 + t2;
Info<< t3 << endl;
tensor t4(3,-2,1,-2,2,0,1, 0, 4);
Info<< inv(t4) << endl;
Info<< (inv(t4) & t4) << endl;
Info<< t1.x() << t1.y() << t1.z() << endl;
Info<< t1.T() << endl;
Info<< det(t1) << endl;
scalar s1(0.75);
Info<< pos(s1) << endl;
Info<< Foam::asinh(s1) << endl;

Info << "========================================= " << endl;

dimensionedTensor sigma
(
"sigma",
dimensionSet( 1, -1, -2, 0, 0, 0, 0),
tensor( 1e6, 0, 0, 0, 1e6, 0, 0, 0, 1e6)
);
Info<< "Sigma: " << sigma << endl;

Info<< "Sigma name: " << sigma.name() << endl;
Info<< "Sigma dimensions: " << sigma.dimensions() << endl;
Info<< "Sigma value: " << sigma.value() << endl;

Info << "========================================= " << endl;

tensorField tf1(2, tensor::one);
Info<< "tf1: " << tf1 << endl;
tf1[0] = tensor(1, 2, 3, 4, 5, 6, 7, 8, 9);
Info<< "tf1: " << tf1 << endl;
Info<< "2.0*tf1: " << 2.0*tf1 << endl;
Info << "========================================= " << endl;




return 0;
}