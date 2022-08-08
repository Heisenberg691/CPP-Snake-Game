#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

using namespace std;

class TextureManager
{
    static map<string, sf::Texture*> textures;
 
    static std::vector<string> order;

    
public:
    
    TextureManager();
   
    ~TextureManager();

    static int getLength();

    static sf::Texture* getTexture(string name);


    static sf::Texture* getTexture(int index);


    static sf::Texture* loadTexture(string name, string path);
};

#endif

