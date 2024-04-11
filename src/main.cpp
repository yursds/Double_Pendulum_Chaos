#include "../include/double_pendulum.h"

int main()
{   
    /* Gaussian distribution */
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> dist(0.0, VARIANCE);

    /* Video */
    sf::ContextSettings settings;
    sf::RenderWindow window;
    sf::Event event;
    
    /* Graphic parameters*/    
    sf::Color traceColor1(sf::Color(0, 138, 224, 255));
    sf::Color traceColor2(sf::Color(0, 150, 120, 255));
    sf::Color circle1Color(sf::Color::Transparent);
    sf::Color circle2Color(sf::Color(0, 255, 255, 255));
    sf::Color circlebis2Color(sf::Color(0, 200, 150, 255));
    sf::Color line1Color(sf::Color(221,38,95,255));
    sf::Color line2Color(sf::Color(221,38,95,255));
    float perturbation;
    float mirror_offset;
    float treshold = NUM_PENDULUM/2;
    bool Run = false;

    /* Dynamic variables */
    std::vector<doublePendulum> pendulum_vec(NUM_PENDULUM);
    std::vector<doublePendulumGraphic> pendulumGraphic_vec(NUM_PENDULUM);
    sf::Clock clock;
    float elapsedSeconds;

    settings.antialiasingLevel = 16;
    window.create(sf::VideoMode(WINDOW_W, WINDOW_H), "Double Pendulum", sf::Style::Default, settings);
    window.setFramerateLimit(FPS);

    /* INIT */
    for (int k = 0; k < NUM_PENDULUM; k++) {

        if (k<treshold) init_pendulumGraphic(pendulumGraphic_vec[k], circle1Color, circle2Color, line1Color, line2Color, traceColor1);
        else init_pendulumGraphic(pendulumGraphic_vec[k], circle1Color, circlebis2Color, line1Color, line2Color, traceColor2);

        perturbation = dist(gen);
        init_pendulumDynamic(pendulum_vec[k], perturbation);
    }
    
    while (window.isOpen()) {

        /* INIT CLOCK */
        elapsedSeconds = clock.getElapsedTime().asSeconds();

        /* COMMAND */
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyReleased) {
                command(event, pendulum_vec, Run);
            } 
        }
        
        /* DYNAMIC */
        for(int k=0; k<NUM_PENDULUM; k++){

            if (k<treshold){mirror_offset=0;}
            else {mirror_offset=PI;}
            
            dynamic(pendulum_vec[k], mirror_offset, Run);
            
            pendulumGraphic_vec[k].deg1 = (mirror_offset+pendulum_vec[k].theta1) * (180/PI);
            pendulumGraphic_vec[k].deg2 = (mirror_offset+pendulum_vec[k].theta2) * (180/PI);
        }

        /* GRAPHIC */
        window.clear(sf::Color(12, 20, 27, 255));
        for(int k=0; k<NUM_PENDULUM; k++){
            graphic(window, pendulumGraphic_vec[k], pendulum_vec[k], elapsedSeconds, Run);
        }
        window.display();
    }
}