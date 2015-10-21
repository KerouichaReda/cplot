#pragma once
#include "GL_AreaGraph.h"

class GL_RiemannHistogram : public GL_AreaGraph
{
public:
	GL_RiemannHistogram(Graph &graph) : GL_AreaGraph(graph){ }

	virtual bool has_unit_normals() const{ return true; }
	virtual bool wants_backface_culling() const{ return true; }

	virtual void update(int n_threads, double quality);
};
