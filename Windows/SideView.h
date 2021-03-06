#pragma once
#include "afxwin.h"
#include "Controls/HeaderControl.h"
#include "Controls/SideSectionParams.h"
#include "Controls/SideSectionDefs.h"
#include "Controls/SideSectionGraphs.h"
#include "Controls/SideSectionSettings.h"
#include "Controls/SideSectionStyle.h"
#include "Controls/SideSectionAxis.h"
class Document;
class Graph;
struct Plot;

union BoxState
{
	struct
	{
		bool params   : 1;
		bool defs     : 1;
		bool graphs   : 1;
		bool settings : 1;
		bool axis     : 1;
		bool style    : 1;
	};
	uint32_t all;
};

class SideView : public CScrollView
{
public:
	SideView();
	
	Document &document() const;
	BoxState GetBoxState() const;
	void SetBoxState(BoxState b);

	void Redraw();
	void Recalc(Plot &plot);
	void Recalc(Graph *g);
	void Update(bool full);

	void UpdateParams(bool full) { params.Update(full); if (full) Update(false); }
	void UpdateDefs(bool full) { defs.Update(full); if (full) Update(false); }
	void UpdateGraphs(bool full) { graphs.Update(full); if (full) Update(false); }
	void UpdateSettings(bool full) { settings.Update(full); if (full) Update(false); }
	void UpdateStyle(bool full) { style.Update(full); if (full) Update(false); }
	void UpdateAxis(bool full) { axis.Update(full); if (full) Update(false); }
	void UpdateAll();

	bool Animating() const;
	void Animate();

	int  OnCreate(LPCREATESTRUCT cs);
	BOOL PreCreateWindow(CREATESTRUCT &cs) override;
	BOOL OnEraseBkgnd(CDC *dc);
	void OnSize(UINT type, int w, int h);
	void OnInitialUpdate();
	BOOL OnMouseWheel(UINT flags, short dz, CPoint p);
	void OnDraw(CDC *dc) override;

private:
	int  active_anims;
	void AnimStateChanged(bool active);

	int update_w; // bounds.width in last Update call (to optimize OnSize)

	friend class PlotView; // access to OnXxx methods
	friend class ParameterView; // access to AnimStateChanged
	friend class SideSectionAxis; // access to AnimStateChanged

	SideSectionParams   params;
	SideSectionDefs     defs;
	SideSectionGraphs   graphs;
	SideSectionSettings settings;
	SideSectionStyle    style;
	SideSectionAxis     axis;

	DECLARE_DYNCREATE(SideView)
	DECLARE_MESSAGE_MAP()
};

