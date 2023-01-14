#include <cstdlib>
#include <ctime>

#include "devices/Window.h"
#include "renderer/camera/Camera.h"
#include "renderer/gui/GUI.h"
#include "simulation/Earth.h"
#include "simulation/RingedPlanet.h"
#include "simulation/Skybox.h"
#include "simulation/SolarSystem.h"
#include "selection/MouseSelector.h"

#include "utils/logging/ConsoleLogger.h"

int main()
{
    std::srand((unsigned int)std::time(nullptr));
    Window& window = Window::GetInstance();

    Camera camera;
    camera.bind();

    SolarSystem solarSystem;
    solarSystem.addPlanet(new Planet("mercury", 0.3f, 100.f, 2.0f, 0.47f, 20.0f));
    solarSystem.addPlanet(new Planet("venus", 0.95f, 100.f, 2.0f, 0.35f, 25.0f));
    solarSystem.addPlanet(new Earth());
    solarSystem.addPlanet(new Planet("mars", 0.5f, 100.f, 2.0f, 0.24f, 35.0f));
    solarSystem.addPlanet(new Planet("jupiter", 5.0f, 100.f, 2.0f, 0.13f, 50.0f));
    solarSystem.addPlanet(new RingedPlanet("saturn", 4.5f, 100.f, 0.2f, 0.09f, 70.0f, 1.0f, 7.0f));
    solarSystem.addPlanet(new Planet("uranus", 3.2f, 100.f, 2.0f, 0.05f, 90.0f));
    solarSystem.addPlanet(new Planet("neptune", 3.3f, 100.f, 2.0f, 0.04f, 110.0f));

    Skybox skybox("universe");
    MouseSelector mouseSelector(solarSystem);
    GUI gui(mouseSelector);

    const auto& logger = ConsoleLogger::INSTANCE;
    logger.log("Hello motherfucker!");

    return 0;

    while (!window.shouldClose())
    {
        window.update();
        camera.update();
        solarSystem.update();
        mouseSelector.update();

        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        solarSystem.render();
        skybox.render();
        gui.render();
    }

    return 0;
}