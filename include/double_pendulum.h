#ifndef DOUBLE_PENDULUM
#define DOUBLE_PENDULUM

#include <iostream>
#include <cmath>
#include <random>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <vector>

#define FPS             60
#define TRAILSIZE       100
#define NUM_PENDULUM    200

/* Dynamic parameters*/
#define M1              5.3
#define M2              3.5
#define L1              220
#define L2              250
#define G               0.1
#define TIMESCALE       1
#define DAMPING         1.0f
#define VARIANCE        0.0001

/* Graphic parameters*/
#define TIMESHADE       40
#define THICKNESS       0.2
#define RADIUS          5
#define WINDOW_W        1920
#define WINDOW_H        1080
#define WINDOW_Ox       WINDOW_W/2
#define WINDOW_Oy       WINDOW_H/2
#define THETA1_INIT     M_PI/2+0.5
#define THETA2_INIT     M_PI/2+0.5


constexpr double PI = M_PI;

struct doublePendulum{
    float mass;
    float lenght1;
    float lenght2;
    float p0x;
    float p0y;
    float p1x;
    float p1y;
    float theta1;
    float theta2;
    float dtheta1;
    float dtheta2;
};

struct doublePendulumGraphic{
    float deg1;
    float deg2;
    sf::CircleShape circle1;
    sf::CircleShape circle2;
    sf::RectangleShape line1;
    sf::RectangleShape line2;
    sf::Color circleColor1;
    sf::Color circleColor2;
    sf::Color line1Color;
    sf::Color line2Color;
    sf::Color traceColor;
    std::vector<sf::Vector2f> trail;
};

void init_pendulumGraphic(doublePendulumGraphic &p, sf::Color circ1, sf::Color circ2, sf::Color rod1, sf::Color rod2, sf::Color trace);

void init_pendulumDynamic(doublePendulum &p, float offset);

void dynamic(doublePendulum &p, float mirror_offset, bool flag);

void command(sf::Event &event, std::vector<doublePendulum> &p_vec, bool &flag);

void graphic(sf::RenderWindow &window,  doublePendulumGraphic &pG, doublePendulum p, float time, bool flag);

#endif