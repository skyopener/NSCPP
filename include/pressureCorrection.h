#ifndef _PRESSURE_HPP
#define _PRESSURE_HPP

#include<iostream>
#include <blitz/array.h>

//Poisson Equation IML++
#include "gmres.h"
#include "coord_double.h"
#include "iotext_double.h"
#include MATRIX_H

//NS++ 
#include "Mesh.h"
#include "presicion.h"

using blitz::Array;


class PressureCorrect
{
public:
    PressureCorrect(
                    Array<real,2>& vel_u, 
                    Array<real,2>& vel_v,
                    Array<real,2>& press_p,
                    Array<real,2>& Bound_u,
                    Array<real,2>& Bound_v,
                    MeshTool::MeshBlock &Grid_set   
	                )
    : uS(vel_u), 
      vS(vel_v), 
      pressure(press_p),
      uBoundary(Bound_u),
      vBoundary(Bound_v),
      Grid(Grid_set)
    { 

    std::cout << "Building Pressure Equation " << std::endl;
    /**
     Gives the Pressure size to the Divergence
     all this equation is discretized in the Cell place.
    **/

        D.resize(pressure.shape()); 
        elements = 13*Grid.cNx*Grid.cNy - 12*(Grid.cNx+Grid.cNy);


        val2 = new real[elements];
        row2 = new int[elements];
        col2 = new int[elements];

        std::cout << "elements: "<< elements << std::endl;

    }

    void Div();
    void Update();
    void FillPoisson();

private:
    //Velocities located in the staggered place.
    const Array<real,2>& uS;
    const Array<real,2>& vS;

    const Array<real,2>& pressure; 

    //these arrays contain the Ghost Boundary nodes.   
    const Array<real,2>& uBoundary;    
    const Array<real,2>& vBoundary;    
    const MeshTool::MeshBlock & Grid; 
    int elements; 
    
    //Poisson equation Matrix definition
    real *val2;
    int *row2;
    int *col2;

    Coord_Mat_double A; 


    //Divergence Array
    Array<real,2> D;
};

#endif
