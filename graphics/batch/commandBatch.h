#pragma once

#include "batch.h"

#include "../shader/shader.h"

namespace P3D::Graphics {

template<typename Vertex, typename Command>
class CommandBatch : public Batch<Vertex> {
protected:
	std::vector<Command> commandBuffer;

	size_t currentIndexOffset;
public:
	CommandBatch(BatchConfig config) : Batch<Vertex>(config), currentIndexOffset(0) {

	}

	virtual void pushCommand(Command command) {
		size_t count = Batch<Vertex>::indexBuffer.size() - currentIndexOffset;

		if (count == 0)
			return;

		commandBuffer.push_back(command);
		currentIndexOffset += count;
	}

	virtual void submit() {

	};

	virtual void clear() {
		currentIndexOffset = 0;
		Batch<Vertex>::clear();
		commandBuffer.clear();
	}
};

};