#ifndef SMUFERS_GAMEMAP_H
#define SMUFERS_GAMEMAP_H
#include <vector>
#include "Layer.hpp"
class GameMap{
public:
    void Render(){
        for(unsigned int i=0; i<m_MapLayers.size(); i++   )
            m_MapLayers[i]->Render();
    }

    void Update(){
        for(unsigned int i=0; i<m_MapLayers.size(); i++   )
            m_MapLayers[i]->Update();

    }
    std::vector<Layer*>GetMapLayers(){return m_MapLayers;}

private:
    std::vector<Layer*>m_MapLayers;





};




#endif //SMUFERS_GAMEMAP_H