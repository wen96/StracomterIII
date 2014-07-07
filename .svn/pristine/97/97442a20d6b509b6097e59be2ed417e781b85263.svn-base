/* 
 * File:   Texture.h
 * Author: sempere
 *
 * Created on 10 / gener / 2012, 21:53
 */

#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <GL/gl.h>
#include <GL/glu.h>


using namespace std;

//enum WrapMode{
//	REPEAT,CLAM_TO_EDGE,CLAM_TO_MIRROR
	//Nowadays, we don't have border
//};

//enum MagnificationFilter{
	//LINEAR,NEAREST	
//}

//enum MinificationFilter{
//	LINEAR,NEAREST,NEAREST_MIPMAP_NEAREST,NEAREST_MIPMAP_LINEAR,LINEAR_MIPMAP_NEAREST, LINEAR_MIPMAP_LINEAR
//}


class Texture
{
	public:
		Texture();
		virtual ~Texture() {target = -1;};
		void bind();
				
	protected:
		Texture(const Texture&) {};
		GLuint id;
		GLenum target;
		GLint levelOfDetail;
		GLint internalFormat;
		GLsizei width;
		GLsizei height;
		GLint pixelFormat;
		GLint border;
		GLint textureDatatype;
		GLvoid* texels;
		GLint minificationFilter;
		GLint magnificationFilter;
		GLint wrapMode;
		static int idCount;

};

class TextureImage : public Texture {
public:
	 TextureImage(string file);
      
	virtual ~TextureImage();
	

private:
	
	
	string file;

} ;	


#endif	

