#include "PipeNetwork.hpp"
#include <iostream>
#include <fstream>
#include "linalg.hpp"

using namespace std;

namespace cie {

    namespace pipenetwork {

        PipeNetwork::PipeNetwork(string filename) : filename_(filename)
        {
            cout << "\t Setting up Pipe Network" << endl;
            std::ifstream infile(filename_);                        //opening input file
            double numberOfValues, K;
            infile >> numberOfValues;                               // reading no. of nodes
            //cout << numberOfValues;
            infile >> K;                                            // and no. of tubes
            //cout << " " << K;

            nodes.reserve(numberOfValues);

            for (int i = 0; i < numberOfValues; ++i)
            {
                std::vector<double> data;
                for (int j = 0; j < 3; ++j)
                {
                    double value;
                    infile >> value;                                   //reading the node data and storing it in a temp vector data
                    data.push_back(value);
                }
                nodes.push_back(Node(data[0], data[1], data[2], i));   //Creating a node with the data in vect data.
            }

            tubes.reserve(K);
            for (int i = 0; i < K; ++i)
            {
                std::vector<double> data2;
                for (int j = 0; j < 3; ++j)
                {
                    double value;
                    infile >> value;
                    data2.push_back(value);
                }
                tubes.push_back(Tube((&nodes[data2[0]]), &(nodes[data2[1]]), data2[2]));

                // nodes r set in order. id = 0 -> is nodes[0] soo we can read value
                // of tube node. tube n1 = nodes[value]
            }


            cout << "\t Pipe_Network created" << endl;


        }

        std::vector<double> PipeNetwork::computeFluxes() const
        {
            cie::linalg::Matrix B(nodes.size(), nodes.size(), 0);                       // setting up a B matrix with 0's
            for (size_t i = 0; i < this->tubes.size(); i++)                             // for no. of tubes, calculating 
            {                                                                           //permeability and adding to B matrix
                Node n1 = *(this->tubes[i].node1());
                Node n2 = *(this->tubes[i].node2());                                   // retriving data about Node in a Single Tube
                int id1 = n1.id();                                                     // n1 and n2 are temporary nodes to obtain IDs.
                int id2 = n2.id();
                double per = this->tubes[i].permeability();                            // storing permeability of a tube in variable per 

                B(id1, id1) += per;
                B(id2, id2) += per;                                                     // setting up elements in the matrix
                B(id1, id2) -= per;
                B(id2, id1) -= per;


            }


            std::vector < double > Q(this->nodes.size(), 0);                            //setting up matrix Q with 0's for flowrate cal
            for (size_t i = 0; i < this->nodes.size(); i++)
            {
                Q[i] = -(this->nodes[i].flow());                                       //obtaining flows from nodes
            }

            for (size_t i = 0; i < this->nodes.size(); i++)                             // As an absolute height of the system is not specified
            {
                B(i, 0) = 0;                                                            // Including a boundary condition
                B(0, i) = 0;                                                            // by defining an absolute height of one node
            }
            B(0, 0) = 1;                                                                // h1 = 0, therefore B(0,0) = 1.
            Q[0] = 0;

            std::vector<double> h(this->nodes.size(), 0);                               // setting up a h vector according to no. of nodes. 
            h = cie::linalg::solve(B, Q);                                               // calling solve from linalg Lib.

            std::vector< double> q(this->tubes.size(), 0);                              // setting up a flux vector q with 0's. Each tube has a flux
            for (size_t i = 0; i < this->tubes.size(); i++)
            {
                
                Node n1 = *this->tubes[i].node1();
                                                                //int h1 = (*tubes[i].node1()).id();
                int h1 = n1.id();                                                      // retriving required id values of nodes for delta h calc.
                Node n2 = *this->tubes[i].node2();
                int h2 = n2.id();
                double B_i = this->tubes[i].permeability();                            // permeability of that Tube.

                q[i] = B_i * (h[h1] - h[h2]);
            }
            //cout << endl << "\t Q[ ] = ";
            //cie::linalg::write(q);
            return q;
        }
    }//namespace pipenetwork
}//namespace cie
