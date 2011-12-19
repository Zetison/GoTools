//===========================================================================
//                                                                           
// File: GapRemoval.h
//                                                                           
// Created: Nov. 2009
//                                                                           
// Author: Vibeke Skytt, SINTEF
//                                                                           
// Revision:
//                                                                           
// Description:
//                                                                           
//===========================================================================

#ifndef _GAPREMOVAL_H
#define _GAPREMOVAL_H

#include "GoTools/geometry/SplineCurve.h"
#include "GoTools/geometry/SplineSurface.h"
#include "GoTools/geometry/CurveOnSurface.h"
#include "GoTools/geometry/BsplineBasis.h"
#include "GoTools/geometry/BoundedSurface.h"
#include "GoTools/creators/ConstraintDefinitions.h"

namespace Go {

  // Removal of gaps between two adjacent surfaces of various types

namespace GapRemoval
{

  // Both surfaces are non-trimmed spline surfaces and the
  // common boundary are described by CurveOnSurface entities
  void
  removeGapSpline(shared_ptr<SplineSurface>& srf1, 
		  shared_ptr<CurveOnSurface>& bd_cv1,
		  double start1, double end1,
		  shared_ptr<SplineSurface>& srf2, 
		  shared_ptr<CurveOnSurface>& bd_cv2,
		  double start2, double end2, Point vertex1, Point vertex2,
		  double epsge, bool *same_orientation = NULL);

  // Both surfaces are trimmed of some type and the
  // common boundary are described by CurveOnSurface entities
  double
  removeGapTrim(shared_ptr<CurveOnSurface>& bd_cv1,
		double start1, double end1,
		shared_ptr<CurveOnSurface>& bd_cv2,
		double start2, double end2, Point vertex1, Point vertex2,
		double epsge);

  bool
  removeGapSplineTrim(shared_ptr<SplineSurface>& srf1, 
		      std::vector<shared_ptr<CurveOnSurface> >& bd_cv1,
		      std::vector<double> start1, 
		      std::vector<double> end1,
		      std::vector<shared_ptr<CurveOnSurface> >& bd_cv2,
		      std::vector<double> start2, 
		      std::vector<double> end2, Point vertex1, 
		      Point vertex2, double epsge);

  void modifySplineSf(shared_ptr<ParamSurface>& srf1, 
		      std::vector<shared_ptr<CurveOnSurface> >& bd_cv1,
		      std::vector<double> start1, std::vector<double> end1,
		      shared_ptr<ParamSurface>& srf2, 
		      std::vector<shared_ptr<CurveOnSurface> >& bd_cv2,
		      std::vector<double> start2, std::vector<double> end2, 
		      double epsge);

  void modifySplines(shared_ptr<ParamSurface>& srf1, 
		     std::vector<shared_ptr<CurveOnSurface> >& bd_cv1,
		     std::vector<double>& start1, std::vector<double>& end1,
		     shared_ptr<ParamSurface>& srf2, 
		     std::vector<shared_ptr<CurveOnSurface> >& bd_cv2,
		     std::vector<double>& start2, std::vector<double>& end2, 
		     std::vector<Point>& vertex, double epsge);
//
  void
    removeGapSpline2(std::vector<shared_ptr<CurveOnSurface> >& bd_cv1,
		     std::vector<double>& start1, std::vector<double>& end1,
		     std::vector<shared_ptr<CurveOnSurface> >& bd_cv2,
		     std::vector<double>& start2, std::vector<double>& end2, 
		     std::vector<Point>& vertex, double epsge);

  std::vector<shared_ptr<sideConstraintSet> > 
    getCoefConstraints(shared_ptr<SplineCurve>& crv1, int idx1,
		       shared_ptr<SplineCurve>& crv2, int idx2, 
		       double tol);

  shared_ptr<SplineCurve>
    replaceCurvePiece(shared_ptr<SplineCurve> crv,
		      shared_ptr<SplineCurve> sub_crv,
		      double par1, int cont1, 
		      double par2, int cont2);

  shared_ptr<SplineSurface> 
    getSplineAndBd(shared_ptr<ParamSurface> psurf,
		   std::vector<shared_ptr<CurveOnSurface> >& bd_crvs);

  void 
    getBoundarySamples(std::vector<shared_ptr<CurveOnSurface> >& all_bd,
		       std::vector<shared_ptr<CurveOnSurface> >& bd_cvs,
		       std::vector<double>& pts, std::vector<double>& pars,
		       std::vector<int>& bd_idx, double epsge);

  bool modifyAtVertex(shared_ptr<SplineSurface> srf,
		      Point face_param, Point vertex,
		      double epsge);

void 
  checkBoundaryDist(shared_ptr<CurveOnSurface> bd1,
		    shared_ptr<CurveOnSurface> bd2,
		    double start1, double end1,
		    double start2, double end2,
		    int nmb_sample, double& mdist1,
		    double& mdist2);

} // of namespace CreatorsUtils.

}; // end namespace Go



#endif // _GAPREMOVAL_H
