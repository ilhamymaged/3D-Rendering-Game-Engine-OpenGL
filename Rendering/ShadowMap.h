#pragma once
#include <glad/glad.h>

class ShadowMap
{
public:
	ShadowMap(int width, int height);
	~ShadowMap();

	void bind() const;
	void bindFBO() const;

	inline GLuint getDepthMap() { return depthMap; };

private:
	int width;
	int height;
	GLuint depthMapFBO;
	GLuint depthMap;
};