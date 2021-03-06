/*
 * Copyright (C) 1998, 2000-2007, 2010, 2011, 2012, 2013 SINTEF ICT,
 * Applied Mathematics, Norway.
 *
 * Contact information: E-mail: tor.dokken@sintef.no                      
 * SINTEF ICT, Department of Applied Mathematics,                         
 * P.O. Box 124 Blindern,                                                 
 * 0314 Oslo, Norway.                                                     
 *
 * This file is part of GoTools.
 *
 * GoTools is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version. 
 *
 * GoTools is distributed in the hope that it will be useful,        
 * but WITHOUT ANY WARRANTY; without even the implied warranty of         
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public
 * License along with GoTools. If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * In accordance with Section 7(b) of the GNU Affero General Public
 * License, a covered work must retain the producer line in every data
 * file that is created or manipulated using GoTools.
 *
 * Other Usage
 * You can be released from the requirements of the license by purchasing
 * a commercial license. Buying such a license is mandatory as soon as you
 * develop commercial activities involving the GoTools library without
 * disclosing the source code of your own applications.
 *
 * This file may be used in accordance with the terms contained in a
 * written agreement between you and SINTEF ICT. 
 */

#include <fstream>
#include "GoTools/trivariate/SplineVolume.h"
#include "GoTools/geometry/ObjectHeader.h"
#include "GoTools/utils/errormacros.h"
#include "GoTools/geometry/BsplineBasis.h"

using namespace Go;
using namespace std;

int main(int argc, char* argv[] )
{
  if (argc != 5 && argc != 6)
    {
      cout << "Usage: " << argv[0] << "infile outfile direction(0,1, or 2) #surfaces(>=2)" << endl;
      cout << "   Or: " << argv[0] << "infile outfile direction(0,1, or 2) 1 parameter" << endl;
      exit(-1);
    }
 
  int nmbsurfs = atoi(argv[4]);
  if (argc != 5 + (nmbsurfs == 1))
    {
      cout << "Usage: " << argv[0] << "infile outfile direction(0,1, or 2) #surfaces(>=2)" << endl;
      cout << "   Or: " << argv[0] << "infile outfile direction(0,1, or 2) 1 parameter" << endl;
      exit(-1);
    }

  // Open input surface file
  ifstream is(argv[1]);
  ALWAYS_ERROR_IF(is.bad(), "Bad or no input filename");

  ObjectHeader head;
  is >> head;

  // Read volume from file
  SplineVolume vol;
  is >> vol;

  // Open outfile
  ofstream os(argv[2]);
  ALWAYS_ERROR_IF(os.bad(), "Bad or no output filename");

  int pardir = atoi(argv[3]);

  double param;
  double step;
  if (nmbsurfs == 1)
    {
      param = atof(argv[5]);
      step = 0.0;
    }
  else
    {
      const BsplineBasis& b = vol.basis(pardir);
      param = b.startparam();
      step = (b.endparam() - param) / (double)(nmbsurfs - 1);
    }

  for (int i = 0; i < nmbsurfs; ++i)
    {
      SplineSurface* ss;
      ss = vol.constParamSurface(param, pardir);
      ss->writeStandardHeader(os);
      ss->write(os);
      param += step;
    }

}





