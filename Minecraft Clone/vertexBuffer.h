#pragma once

#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

class VertexBuffer {
public:
	unsigned int id;
	int type;
	bool dynamic;

	VertexBuffer(int type);
	void bind();
	void destroy();
	void buffer(void* data, size_t offset, size_t count, float sizeOfData);
};

#endif