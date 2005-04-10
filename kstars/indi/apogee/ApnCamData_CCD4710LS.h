/////////////////////////////////////////////////////////////
//
// ApnCamData_CCD4710LS.h:  Interface file for the CApnCamData_CCD4710LS class.
//
/////////////////////////////////////////////////////////////

#include "ApnCamData.h"

class CApnCamData_CCD4710LS : public CApnCamData
{
public:
	CApnCamData_CCD4710LS();
	virtual ~CApnCamData_CCD4710LS();

	void Initialize();

private:

	void set_vpattern();

	void set_hpattern_clamp_sixteen();
	void set_hpattern_skip_sixteen();
	void set_hpattern_roi_sixteen();

	void set_hpattern_clamp_twelve();
	void set_hpattern_skip_twelve();
	void set_hpattern_roi_twelve();

	void set_hpattern(	APN_HPATTERN_FILE	*Pattern,
						unsigned short		Mask,
						unsigned short		BinningLimit,
						unsigned short		RefNumElements,
						unsigned short		SigNumElements,
						unsigned short		BinNumElements[],
						unsigned short		RefPatternData[],
						unsigned short		SigPatternData[],
						unsigned short		BinPatternData[][APN_MAX_PATTERN_ENTRIES] );

};

 
