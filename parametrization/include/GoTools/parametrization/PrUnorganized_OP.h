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

#ifndef PRUNORGANIZED_OP_H
#define PRUNORGANIZED_OP_H

#include "GoTools/parametrization/PrOrganizedPoints.h"
#include "GoTools/parametrization/PrCellStructure.h"
#include "GoTools/utils/Array.h"
using Go::Vector3D;
using Go::Vector2D;

/** PrUnorganized_OP - This class represents a set of points in three dimensions.
 * All we know about them is their boundary in sequence.
 * No other topology is given.
 * This kind of data can be parametrized by PrParametrizeBdy and PrParametrizeInt.  
 */
class PrUnorganized_OP : public PrOrganizedPoints
{
private:
  PrCellStructure cellstruct_;
  vector<Vector2D> uv_;
  int nInt_; // no of interior points,
             // so xyz_(0),...,xyz_(nInt_-1) are the interior points
             // and xyz_(nInt_),...,xyz_(xyz_.size()-1) are the boundary points
             // in an anticlockwise order.
  double radius2_; // square of radius of epsilon ball.
  int knearest_; // number of points in neighbourhood (alternative to radius)
  int use_k_; // = 1 use k nearest, = 0 use fixed radius

public:
  /// Constructor
  PrUnorganized_OP(int num_cells = 10);
  /// Constructor
  PrUnorganized_OP(int n, int n_int, double* xyz_points, int num_cells = 10);
  /// Empty destructor
  ~PrUnorganized_OP() {};

  /** @name Derived from base class */
  //@{

  /// return the number of nodes in the graph. 
  virtual int       getNumNodes() {return cellstruct_.getNumNodes(); }

  /// return the i-th node in the graph if the nodes are three-dimensional
  virtual Vector3D get3dNode(int i) {return cellstruct_.get3dNode(i); }

  virtual void       set3dNode(int i, const Vector3D& p)
           {cellstruct_.set3dNode(i, p);}
  /// Return the indices of the neighbours of the i-th node.
  /// (here there is no ordering: it's not a planar graph).
  virtual void       getNeighbours(int i, vector<int>& neighbours);

  /// is the i-th node a boundary node or interior node?
  virtual bool    isBoundary(int i) {return (i >= nInt_ ? 1 : 0);}

  /// return the u parameter value of the i-th node.
  virtual double getU(int i) {return uv_[i].x(); }

  /// return the v parameter value of the i-th node.
  virtual double getV(int i) {return uv_[i].y(); }

  /// reset the u parameter value of the i-th node.
  virtual void setU(int i, double u) {uv_[i].x() = u; }

  /// reset the v parameter value of the i-th node.
  virtual void setV(int i, double v) {uv_[i].y() = v; }
  //@}

  /** @name Other functions */
  //@{

  /// get the specified radius for defining neighbours by distance
  double getRadius()
  {
#ifdef __BORLANDC__
    return std::sqrt(radius2_);
#else
    return sqrt(radius2_);
#endif
  }
  /// specify the radius for defining neighbourhood by distance
  void setRadius(double radius) {radius2_ = radius * radius; }
  /// specify a number for defining neighbourhoods by a fixed number
  /// of neighbours.
  void setKNearest(int knearest) {knearest_ = knearest; }
  /// Use a fixed number of neighbours to define the neighbourhood of a 
  /// point.
  void useK() {use_k_ = 1; }
  /// Use an euclidean distance to define the neighbourhood of a point.
  void useRadius() {use_k_ = 0; }


  /// Write contents to stream  
  void print(std::ostream& os);
  /// read contents from stream
  void scan(std::istream& is);
  /// print raw data (no parameterization)
  void printRawData(std::ostream& os);
  /// scan raw data (no parameterization) 
  void scanRawData(std::istream& is, int num_cells, double noise);
  //@}

};


/*>PrUnorganized_OP-syntax: */

/*Class:PrUnorganized_OP

Name:              PrUnorganized_OP
Syntax:	           @PrUnorganized_OP-syntax
Keywords:
Description:       This class represents a set of poits in three dimensions.
                   All we know about them is their boundary in sequence.
                   No other topology is given.
                   This kind of data can be parametrized by PrParametrize.
Member functions:
                   "getNumNodes()" --\\
                   Return the number of nodes in the graph.
                 
                   "get3dNode(int i)" --\\
                   Return the i-th node in the graph if the nodes are 
                   three-dimensional

                   "getNeighbours(int i, PrListInt& neighbours)" --\\
                   Return the indices of the neighbours of the i-th node
                   (here there is no ordering: it's not a planar graph).

                   "isBoundary(int i)" --\\
                   Is i a boundary node or interior node?

Constructors:
Files:
Example:


See also:
Developed by:      SINTEF Applied Mathematics, Oslo, Norway
Author:	           Michael Floater, SINTEF
Date:              Oct. 97
*/

#endif // PRUNORGANIZED_OP_H
