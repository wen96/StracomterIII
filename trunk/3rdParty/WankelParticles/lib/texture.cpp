/* 
 * File:   Texture.cpp
 * Author: sempere
 * 
 * Created on 10 / gener / 2012, 21:52
 */

#include "texture.hpp"
#include "SOIL.h"
int Texture::idCount = 0;

Texture::Texture(){
	//target = -1;
	//id = idCount;
	//idCount++;
}



void
Texture::bind(){
	glBindTexture(GL_TEXTURE_2D,id);
}


TextureImage::TextureImage(string file): Texture(){
    
    int w,h,ch; 
	this-> file = file;
	
	target = GL_TEXTURE_2D;
	levelOfDetail = GL_TEXTURE_MAX_LOD;
	pixelFormat = GL_RGB;
	textureDatatype = GL_UNSIGNED_BYTE;
	internalFormat = GL_RGB;
	border = 0;
	minificationFilter = GL_LINEAR;
	magnificationFilter = GL_NEAREST;
	wrapMode = GL_REPEAT;
	glClearColor(0.0,0.0,0.0,0.0);
    texels = NULL;
    texels = SOIL_load_image(file.c_str(),&w,&h,&ch,SOIL_LOAD_AUTO);
	
	this-> width = w;
	this-> height = h;
    glGenTextures(1,&id);
    glBindTexture(target,id);
    glTexParameteri(target,GL_TEXTURE_MAG_FILTER,magnificationFilter);
    glTexParameteri(target,GL_TEXTURE_MIN_FILTER,minificationFilter);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,w,h,0,GL_RGB,GL_UNSIGNED_BYTE,texels);
    cout <<texels <<" " <<w <<" " <<h <<" " <<ch <<endl;
    //~ glTexImage2D(target,levelOfDetail,internalFormat,width,height,border,pixelFormat,textureDatatype,texels);
    //glGenerateMipmap(GL_TEXTURE_ 2D);
    //~ glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
    
    
	
	
}


TextureImage::~TextureImage() {
    glDeleteTextures(1,&id);
    //delete(texels);
}

