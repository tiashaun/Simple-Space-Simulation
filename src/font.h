#include	<OpenGL/gl.h>

namespace Font {
	struct font_data {
		float		height;										
		GLuint	*textures;									 
		GLuint	list_base;								

		void init( const char *fname, unsigned int height );
		void clean();
	};
	
	void print(const font_data &ft_font, float x, float y, const char *fmt, ...);
}
