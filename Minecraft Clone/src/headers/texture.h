#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

class Texture {
	public: 
		unsigned int id;
		int type;

		Texture(int type);

		void bind();
		void loadFromPath(const char* filePath);
};

#endif