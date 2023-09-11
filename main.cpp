#include <array>
#include <SDL2/SDL.h>
#include "slib.h"
#include "constants.h"
#include "ObjParser.hpp"
#include "sMaths.hpp"
#include "utils.hpp"
#include "Renderer.hpp"
#include "Renderable.hpp"

template <typename T>
T customClamp(const T& value, const T& minValue, const T& maxValue) {
    if (value < minValue) {
        return minValue;
    } else if (value > maxValue) {
        return maxValue;
    } else {
        return value;
    }
}

float totalYaw = 0.0f;
float totalPitch = 0.0f;
float rotationSpeed = 0.1f;


int main()
{
    FPSCounter fpsCounter;
    Clock clock;
    SDL_Window* window = SDL_CreateWindow("3D Software Renderer", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    
    SDL_Init(SDL_INIT_EVERYTHING);
    //SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);
    //SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRelativeMouseMode(SDL_TRUE);
    SDL_WarpMouseInWindow(window, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    slib::vec2 lastMousePos = { SCREEN_WIDTH/2, SCREEN_HEIGHT/2  };
    bool mouseMotion = false;

    SDL_bool loop = SDL_TRUE;
    SDL_Event event;

    slib::texture texture = slib::DecodePng("resources/spyro.png");
    slib::texture skyboxTexture = slib::DecodePng("resources/clouds.png");
    //Mesh* utahMesh = ObjParser::ParseObj("resources/utah.obj");
    //Mesh* bunnyMesh = ObjParser::ParseObj("resources/bunny.obj", texture);
    //Mesh* suzanneMesh = ObjParser::ParseObj("resources/suzanne.obj", texture);
    Mesh* cubeMesh = ObjParser::ParseObj("resources/spyro.obj", texture);
    Mesh* skyboxMesh = ObjParser::ParseObj("resources/skybox.obj", skyboxTexture);
//    auto* bunnyInstance1 = new Renderable(*bunnyMesh, {0, -0.32, -1.5 }, 
//                                         {0, 20, 0 }, {1,1,1}, {200, 200, 200},
//                                          bunnyMesh->verticies);
//    auto* bunnyInstance2 = new Renderable(*suzanneMesh, {0, -0.1, -15 },
//                                          {0, 20, 0 }, {1,1,1},
//                                          suzanneMesh->verticies);
//    auto* bunnyInstance3 = new Renderable(*suzanneMesh, {3, -0.1, -15 },
//                                          {0, 20, 0 }, {1,1,1},
//                                          suzanneMesh->verticies);
//    auto* utahInstance = new Renderable(*utahMesh, {0, -0.1, -2 }, 
//                                        {0, 90, 0 }, {0.2,0.2,0.2},
//                                        utahMesh->verticies);
//    auto* suzanneInstance = new Renderable(*suzanneMesh, {.2, 0.1, -1.5 }, 
//                                           {0, 0, 0 }, {.1,.1,.1}, { 200, 100, 100 },
//                                           suzanneMesh->verticies);

    auto* cubeInstance = new Renderable(*cubeMesh, {.2, 0, -1.5 },
                                        {0, 0, 0 }, {.2,.2,.2}, { 200, 100, 200 },
                                        cubeMesh->verticies);

    auto* skybox = new Renderable(*skyboxMesh, {0, 0, 0 },
                                  {0, 0, 0 }, {5,5,5}, { 200, 100, 200 },
                                  skyboxMesh->verticies);

    slib::Frustum frustum(0, 0, 0, 0);
    slib::Camera camera({ 0, 0, 3 }, { 0, 0, 0 }, { 0, 0, -1 },
                        { 0, 1, 0 }, zFar, zNear, &frustum);

    auto viewMatrix = glm::lookAt(glm::vec3(camera.pos.x,camera.pos.y,camera.pos.z),
                                  glm::vec3(camera.direction.x, camera.direction.y, camera.direction.z),
                                  glm::vec3(0,1,0));

    auto perspectiveMat = glm::perspective(fov, aspect, zNear, zFar);

    Renderer sRenderer(renderer, &camera, perspectiveMat, viewMatrix);
//    sRenderer.AddRenderable(*bunnyInstance1);
//    sRenderer.AddRenderable(*suzanneInstance);
    sRenderer.AddRenderable(*cubeInstance);
    //sRenderer.AddRenderable(*skybox);
//    sRenderer.AddRenderable(*bunnyInstance2);
//    sRenderer.AddRenderable(*bunnyInstance3);
    bool shouldRotate = true;
    while (loop) {


        clock.tick();
        // Allow quiting with escape key by polling for pending events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                loop = SDL_FALSE;
            }
            else if (event.type == SDL_MOUSEMOTION)
            {
                mouseMotion = true;
            }
            else if (event.type == SDL_KEYDOWN) {
                slib::vec3 fwd = sMaths::normaliseVector(camera.direction - camera.pos);
                slib::vec3 left = sMaths::getCrossProduct(fwd, camera.up);
                slib::vec3 right = sMaths::getCrossProduct(camera.up, fwd);

                //std::cout << fwd.x << ", " << fwd.y << ", " << fwd.z << std::endl;
                switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    loop = SDL_FALSE;
                    break;
                case SDLK_w:
                    camera.pos += fwd * 0.05f;
                    break;
                case SDLK_s:
                    camera.pos -= fwd * 0.05f;
                    break;
                case SDLK_a:
                    camera.direction += left * 0.075f;
                    camera.pos += left * 0.075f;
                    break;
                case SDLK_d:
                    camera.direction += right * 0.075f;
                    camera.pos += right * 0.075f;
                    break;
                case SDLK_UP:SDL_SetRelativeMouseMode(SDL_FALSE);
                    break;
                case SDLK_DOWN:SDL_SetRelativeMouseMode(SDL_TRUE);
                    break;
                case SDLK_SPACE:
                    sRenderer.wireFrame = !sRenderer.wireFrame;
                    shouldRotate = !shouldRotate;
                    break;
                default:loop = SDL_TRUE;
                }
            }
        }

        // Don't do this. Take the mouse coords as screen coords and go back to 3d space by inverting the transforms of the matrix and get the vector to rotate.


        // Screen -> Proj -> View (Camera) -> World



        // Update

        // Scene tree/manager
        // Update mesh positions etc.
        // Scene graph
        // If there could be a concept of a root node and all children are rotated relevant to their parents then
        // that would be awesome. Then, implementing a camera is basically almost done; as it would just involve
        // transforming the root node.

//        bunnyInstance1->eulerAngles.y += 0.01f * clock.delta;
//        bunnyInstance2->eulerAngles.y += 0.01f * clock.delta;
//        bunnyInstance3->eulerAngles.y += 0.01f * clock.delta;

        std::cout << fpsCounter.fps_current << std::endl;
        //cubeInstance->eulerAngles.z += 0.5f;
        //if (shouldRotate) cubeInstance->eulerAngles.y -= 0.2f;

        if (mouseMotion) {
            mouseMotion = false;

            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            slib::vec2 currentMousePosition = { static_cast<float>(mouseX), static_cast<float>(mouseY) };

            slib::vec2 deltaMouse = currentMousePosition - lastMousePos;
            float rotationSpeed = 0.1f;
            deltaMouse *= rotationSpeed;

            float yaw = deltaMouse.x;
            float pitch = deltaMouse.y;
            

            sMaths::rotateVertex(camera.direction, {0, -yaw, 0}, camera.pos);
            sMaths::rotateVertex(camera.direction, {pitch, 0, 0}, camera.pos);

            // Correct the camera's up vector
//            slib::vec3 worldUp = {0, 1, 0};
//            slib::vec3 right = sMaths::getCrossProduct(camera.direction, worldUp);
//            camera.up = sMaths::getCrossProduct(right, camera.direction);
//            sMaths::normaliseVector(camera.up);

            SDL_WarpMouseInWindow(window, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
            lastMousePos = { SCREEN_WIDTH/2, SCREEN_HEIGHT/2 };
        }

        sRenderer.Render();
        fpsCounter.Update();


    }


    //delete utahMesh;
    //delete bunnyMesh;
    //delete suzanneMesh;
    //delete cubeMesh;
    //delete bunnyInstance1;
    //delete suzanneInstance;
    delete cubeMesh;
    delete cubeInstance;
    delete skybox;
    delete skyboxMesh;
//    delete bunnyInstance2;
//    delete bunnyInstance3;

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}