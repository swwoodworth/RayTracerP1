#include "Texture.hpp"

Texture::Texture(){
}

Texture::~Texture() {

}

void Texture::parse(ifstream &povFile) {
   getline(povFile, name);
   
   TGAReader reader;
   pixels = reader.TGARead(name, &texWidth, &texHeight);
}
