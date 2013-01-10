#include "TiledGameWorldCreator.h"
#include "GameWorld.h"

#include "IGraphic.h"
#include "Resource.h"

#include "pugixml\pugixml.hpp"
//#include "RenderableComponent.h"

#include "Game.h"

using namespace K15_Engine;

TiledGameWorldCreator::TiledGameWorldCreator(GameWorld &gameWorld,Resource *resource)
{
	m_gameWorld = &gameWorld;
	m_resource = resource;
}

bool TiledGameWorldCreator::create()
{
	using namespace pugi;

	xml_document document;
	xml_parse_result result = document.load_buffer(m_resource->getContent(),m_resource->getSize());

	std::vector<GraphicPtr> tileList;
	if(result.status == status_ok){
		const xml_node mapinfo = document.child("map");
		
		int width = mapinfo.attribute("width").as_int();
		int height = mapinfo.attribute("height").as_int();

		m_gameWorld->setSize(width,height);

		for(xml_node tilesetinfo = mapinfo.child("tileset"); tilesetinfo;tilesetinfo = tilesetinfo.next_sibling()){
			if(tilesetinfo.child("image")){
				xml_node tilesetimage = tilesetinfo.child("image");
				String tilesetFile = tilesetimage.attribute("source").value();

				Resource *tilesetResource = myGame->getResourceManager()->getResource(tilesetFile);

				if(tilesetResource != NULL){
					int tile_width = tilesetinfo.attribute("tilewidth").as_int();
					int tile_height = tilesetinfo.attribute("tileheight").as_int();

					int tile_spacing = tilesetinfo.attribute("spacing").as_int();
					int tile_margin = 0;//tilesetinfo.attribute("margin").as_int();

					GraphicPtr tilesetImage = myGame->getGraphicManager()->createGraphic(tilesetResource);

					if(tilesetImage->loadedSuccessful()){
						int max_x = tilesetImage->getSize().getWidth() - tile_spacing;
						int max_y = tilesetImage->getSize().getHeight() - tile_spacing;

						//Whole Tileset gets cut into pieces here.
						for(int y = tile_spacing;y < max_y;y += (tile_height + tile_spacing)){
							for(int x = tile_spacing;x < max_x;x += (tile_width + tile_spacing)){
								tileList.push_back(tilesetImage->cutRect(x,y,tile_width,tile_height));
							}
						}
					}

					//Debug::drawAsLine(tileList);
				}
				
				delete tilesetResource;
			}
			
		}

		for(xml_node layerinfo = mapinfo.child("layer"); layerinfo;layerinfo = layerinfo.next_sibling()){
// 			int layer_width = layerinfo.attribute("width").as_int();
// 			int layer_height = layerinfo.attribute("height").as_int();
			String layer_name = layerinfo.attribute("name").value();
			F32 layer_scrollspeed = 1;
			bool layer_collision = false;

			//Properties here
			if(layerinfo.child("properties")){ // Check if the layer has any properties.
				for(xml_node layerproperty = layerinfo.child("properties").child("property"); layerproperty;layerproperty = layerproperty.next_sibling()){
					layer_collision = layerproperty.attribute("collision");

					if(layerproperty.attribute("scrollspeed")){ //Check if scrollspeed has been set
						layer_scrollspeed = layerproperty.attribute("scrollspeed").as_float();
					}

				}
			}
			

			GameWorldLayer layer(layer_name);
			
			if(layer_collision == true){
				layer.setAsCollisionLayer();
			}

			layer.setScrollSpeed(layer_scrollspeed);
			
			//layer.setWidth(layer_width);
			//layer.setHeight(layer_height);

			//Now to the tiles on the map

			int x = 0;
			int y = 0;

			if(layerinfo.child("data")){
				for(xml_node datainfo = layerinfo.child("data").child("tile");datainfo;datainfo = datainfo.next_sibling()){
					U32 data_id = datainfo.attribute("gid").as_int() - 1;

					if(data_id <= tileList.size()){
						GraphicPtr tileGraphic = tileList.at(data_id);
						if(tileGraphic != NULL){
							GameObject curTile;

// 							AnimatedComponent *animcomp = new AnimatedComponent();
// 							Animation anim("Idle");
// 							anim.addAnimationData(AnimationData(tileGraphic,0));
// 							
// 							animcomp->addAnimation(anim); //Add Tile
// 
// 							curTile.addComponent(animcomp);
							VariantList paramList;
							paramList.push_back(tileGraphic);
							AbstractComponent *renderComponent = ComponentFactory::create("RenderableComponent",paramList);

							//RenderableComponent *renderComponent = new RenderableComponent(tileGraphic);
							curTile.addComponent(renderComponent);
							curTile.setPosition(x,y);

							layer.addGameObject(curTile);
						}

						x += tileGraphic->getSize().getWidth();

						if(x >= (width * tileGraphic->getSize().getWidth())){
							x = 0;
							y += tileGraphic->getSize().getHeight();
						}
						
					}
				}
			}
			m_gameWorld->addLayer(layer);
		}

		//Objectgroups
		for(xml_node objectsgroup = document.child("objectgroup");objectsgroup;objectsgroup = objectsgroup.next_sibling()){
			//loop through all objects in this objectsgroup
			for(xml_node curObject = objectsgroup.child("object");curObject;curObject = curObject.next_sibling()){
				GameObject newMapObject;

				if(curObject.attribute("gid")){
					int gid = curObject.attribute("gid").as_int();
				}

				int x = curObject.attribute("x").as_int();
				int y = curObject.attribute("y").as_int();

				newMapObject.setPosition(x,y);

				//width & height
				if(curObject.attribute("width") && curObject.attribute("height")){
					int m_width = curObject.attribute("width").as_int();
					int m_height = curObject.attribute("height").as_int();

					newMapObject.setSize(m_width,m_height);
				}

				//User defined settings
			}
		}

	tileList.clear();

	}else{
		WRITE_ERRORLOG("Could not create GameWorld Object. | " + String(result.description()));
		return false;
	}

	return true;
}