#pragma once

class Part;
class Physical;
class WorldPrototype;
#include "geometry/shape.h"
#include "math/linalg/mat.h"
#include "math/position.h"
#include "math/globalCFrame.h"
#include "math/bounds.h"

struct PartPhysicalData {
	GlobalCFrame cframe;
	Shape hitbox;
	double maxRadius;
	double friction;
	Part* part;
};

struct PartProperties {
	double density;
	double friction;
	double bouncyness;
};

class Part {
	friend class Physical;
	friend class WorldPrototype;

	GlobalCFrame cframe;

public:
	bool isTerrainPart = false;
	Physical* parent = nullptr;
	Shape hitbox;
	double maxRadius;
	PartProperties properties;

	double mass;
	SymmetricMat3 inertia;
	Vec3 localCenterOfMass;

	BoundingBox localBounds;

	/*
		This is extra velocity that should be added to any colission
		if this part is anchored, this gives the velocity of another part sliding on top of it, with perfect friction

		In other words, this is the desired relative velocity for there to be no friction
	*/
	Vec3 conveyorEffect = Vec3(0, 0, 0);

	Part() = default;
	Part(const Shape& shape, const GlobalCFrame& position, const PartProperties& properties);
	~Part();
	bool intersects(const Part& other, Position& intersection, Vec3& exitVector) const;
	void scale(double scaleX, double scaleY, double scaleZ);

	Bounds getStrictBounds() const;

	Position getPosition() const { return cframe.getPosition(); }
	Position getCenterOfMass() const { return cframe.localToGlobal(localCenterOfMass); }
	const GlobalCFrame& getCFrame() const { return cframe; }
	void setCFrame(const GlobalCFrame& newCFrame);

	void attach(Part& other, const CFrame& relativeCFrame);
	void detach();
};
