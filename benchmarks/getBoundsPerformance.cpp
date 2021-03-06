#include "benchmark.h"

#include <Physics3D/geometry/polyhedron.h>
#include <Physics3D/geometry/shapeLibrary.h>
#include <Physics3D/math/linalg/trigonometry.h>

namespace P3D {
class GetBounds : public Benchmark {
	Polyhedron poly;
	double result = 0;
public:
	GetBounds() : Benchmark("getBounds") {}

	void init() override { this->poly = ShapeLibrary::createSphere(1.0, 2); }
	void run() override {
		Mat3f m = rotationMatrixfromEulerAngles(0.1f, 0.05f, 0.7f);
		for(size_t i = 0; i < 10000000; i++) {
			//Mat3 m = rotationMatrixfromEulerAngles(0.1 * (i%5), 0.2 * (i%6), 0.3 * (i%7));

			BoundingBox r = this->poly.getBounds(m);
			result += r.min.x + r.min.y + r.min.z + r.max.x + r.max.y + r.max.z;
		}
	}
} getBounds;
};



