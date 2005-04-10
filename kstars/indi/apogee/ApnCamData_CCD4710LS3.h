/////////////////////////////////////////////////////////////
//
// ApnCamData_CCD4710LS3.h:  Interface file for the CApnCamData_CCD4710LS3 class.
//
/////////////////////////////////////////////////////////////

#include "ApnCamData.h"

class CApnCamData_CCD4710LS3 : public CApnCamData
{
public:
	CApnCamData_CCD4710LS3();
	virtual ~CApnCamData_CCD4710LS3();

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

 
