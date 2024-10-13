#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

class Texture {
	public: 
		unsigned int id;
		int type;
		GLenum unit;

		Texture(int type, GLenum unit);

		void bind();
		void loadFromPath(const char* filePath);
};

#endif