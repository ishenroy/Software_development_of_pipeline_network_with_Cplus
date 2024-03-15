#include <iostream>
#include "PipeNetwork.hpp"
#include "Tube.hpp"
#include "Node.hpp"
#include "linalg.hpp"


using namespace std;

int main() {
    cie::pipenetwork::PipeNetwork Pipe1("in_put.txt");       // passing input file as argument to construct a PipeNetwork called Pipe1

    std::vector<double> flux = Pipe1.computeFluxes();
    cout << endl << " \t FLUX Q[] = " << endl;
    cie::linalg::write(flux);                               // Using write function from linalg Lib.
    cout << endl << "\t ------------END------------ \n \n";
    return 0;
}