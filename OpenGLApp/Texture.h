
#include "Renderer.h"

class Texture
{
public:
	Texture(const std::string& path);
	~Texture();
	void Bind(unsigned int slot = 0) const;
	void UnBind() const;

	inline int GetWidth() const { return m_width; }
	inline int GetHeight() const { return m_height; }

private:
	int m_width;
	int m_height;
	int m_BPP;
	std::string m_path;
	unsigned int m_rendererId;
	unsigned char* m_localBuffer;


};

