#include "indexedMesh.h"
#include "../../engine/geometry/shape.h"
#include "../util/log.h"

IndexedMesh::IndexedMesh(Shape shape) : AbstractMesh(), vertexCount(shape.vertexCount), triangleCount(shape.triangleCount) {
	vertexBuffer = new VertexBuffer(reinterpret_cast<double const *>(shape.vertices), vertexCount * 3);
	normalBuffer = new VertexBuffer(reinterpret_cast<double const *>(shape.normals.get()), vertexCount * 3);
	uvBuffer = new VertexBuffer(reinterpret_cast<double const *>(shape.uvs.get()), vertexCount * 2);

	indexBuffer = new IndexBuffer(reinterpret_cast<unsigned int const *>(shape.triangles), triangleCount * 3);

	vertexBufferLayout.push<double>(3);
	normalBufferLayout.push<double>(3);
	uvBufferLayout.push<double>(2);

	vertexArray->addBuffer(*vertexBuffer, vertexBufferLayout);
	vertexArray->addBuffer(*normalBuffer, normalBufferLayout);
	vertexArray->addBuffer(*uvBuffer, uvBufferLayout);
}

IndexedMesh::IndexedMesh(const double* vertices, const double* normals, const double* uvs, const unsigned int* indices, const int vertexCount, const int triangleCount) : AbstractMesh(), vertexCount(vertexCount), triangleCount(triangleCount) {
	vertexBuffer = new VertexBuffer(vertices, vertexCount * 3);
	normalBuffer = new VertexBuffer(normals, vertexCount * 3);
	uvBuffer = new VertexBuffer(uvs, vertexCount * 2);

	indexBuffer = new IndexBuffer(indices, triangleCount * 3);

	vertexBufferLayout.push<double>(3);
	normalBufferLayout.push<double>(3);
	uvBufferLayout.push<double>(2);

	vertexArray->addBuffer(*vertexBuffer, vertexBufferLayout);
	vertexArray->addBuffer(*normalBuffer, normalBufferLayout);
	vertexArray->addBuffer(*uvBuffer, uvBufferLayout);
}

void IndexedMesh::render()  {
	vertexArray->bind();
	indexBuffer->bind();

	glDrawElements((int) renderMode, triangleCount * 3, GL_UNSIGNED_INT, nullptr);
}

void IndexedMesh::close() {
	vertexBuffer->close();
	indexBuffer->close();
	vertexArray->close();
}
