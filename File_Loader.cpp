#include "File_Loader.h"
#include "Render.h"

#include "SDL/SDL_image.h"

File* File_Loader::Load_File(string file_name){
        File* file = new File(); 
        if(Image_Cache.find(file_name) != Image_Cache.end()){
            file = Image_Cache[file_name];
        }
        else{
            //check if the file_name end with .png
            if(file_name.substr(file_name.size() - 4, 4) == ".png"){
                
                file->Surface = IMG_Load(("IMAGES/" + file_name).c_str());
                file->Texture = SDL_CreateTextureFromSurface(RENDER::Renderer, file->Surface);

                file->Type = FILE_TYPE::PNG;
            }
            else{
                //Load the file as a raw
                ifstream file_stream(file_name);
                if(!file_stream.is_open()){
                    printf("File could not be opened.\n");
                    return nullptr;
                }

                stringstream buffer;
                buffer << file_stream.rdbuf();
                file->Data = buffer.str();
            }

            Image_Cache[file_name] = file;
        }

    return file;
}

void File_Loader::Clear_Cache(){
    //Do the next functions for all objects
    //SDL_DestroyTexture
    //SDL_FreeSurface

    for (auto it = Image_Cache.begin(); it != Image_Cache.end(); it++){
        if(it->second->Type == FILE_TYPE::PNG){
            SDL_DestroyTexture(it->second->Texture);
            SDL_FreeSurface(it->second->Surface);
        }
    }
}