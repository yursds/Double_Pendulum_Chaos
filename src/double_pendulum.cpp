#include "../include/double_pendulum.h"

void init_pendulumGraphic(doublePendulumGraphic &p, sf::Color circ1, sf::Color circ2, sf::Color rod1, sf::Color rod2, sf::Color trace){

    p.circle1.setRadius(RADIUS);
    p.circle2.setRadius(RADIUS);
    p.circle1.setOrigin(sf::Vector2f(RADIUS, RADIUS));
    p.circle2.setOrigin(sf::Vector2f(RADIUS, RADIUS));
    p.line1.setSize(sf::Vector2f(L1, THICKNESS));
    p.line2.setSize(sf::Vector2f(L2, THICKNESS));
    p.circle1.setFillColor(circ1);
    p.circle2.setFillColor(circ2);
    p.line1.setFillColor(rod1);
    p.line2.setFillColor(rod2);
    p.deg1=0;
    p.deg2=0;
    p.traceColor = trace;
}

void init_pendulumDynamic(doublePendulum &p, float offset){

    p.p0x=0;
    p.p0y=0;
    p.p1x=0;
    p.p1y=0;
    p.theta1=THETA1_INIT;
    p.theta2=THETA1_INIT + offset;
    p.dtheta1=0.0;
    p.dtheta2=0.0;
}

void dynamic(doublePendulum &p, float mirror_offset, bool flag){

    float th1, th2, dth1, dth2, ddth1, ddth2, x0, y0, x1, y1;
    float num11, num12, num13, den1, num21, num22, num23, den2;

    th1 = p.theta1;
    th2 = p.theta2;
    dth1 = p.dtheta1;
    dth2 = p.dtheta2;
    
    if(flag){
        num11 = -G * (2 * M1 + M2) * sin(th1);
        num12 = -M2 * G * sin(th1 - 2 * th2);
        num13 = -2 * sin(th1 - th2) * M2 * (dth2 * dth2 * L2 + dth1 * dth1 * L1 * cos(th1 - th2));
        den1 = L1 * (2 * M1 + M2 - M2 * cos(2 * th1 - 2 * th2));
        
        num21 = 2 * sin(th1 - th2);
        num22 = dth1 * dth1 * L1 * (M1 + M2) + G * (M1 + M2) * cos(th1);
        num23 = dth2 * dth2 * L2 * M2 * cos(th1 - th2);
        den2 = L2 * (2 * M1 + M2 - M2 * cos(2 * th1 - 2 * th2));
        
        ddth1 = (num11 + num12 + num13) / den1;
        ddth2 = (num21 * (num22 + num23)) / den2;

        dth1 += ddth1 * TIMESCALE;
        dth2 += ddth2 * TIMESCALE;
        th1 += dth1 * TIMESCALE;
        th2 += dth2 * TIMESCALE;
        dth1 *= DAMPING;
        dth2 *= DAMPING;
    }

    x0 = WINDOW_Ox + L1 * sin(mirror_offset+th1);
    y0 = WINDOW_Oy + L1 * cos(mirror_offset+th1);
    x1 = x0 + L2 * sin(mirror_offset+th2);
    y1 = y0 + L2 * cos(mirror_offset+th2);
    
    p.theta1=th1;
    p.theta2=th2;
    p.dtheta1=dth1;
    p.dtheta2=dth2;    
    p.p0x = x0;
    p.p0y = y0;
    p.p1x = x1;
    p.p1y = y1;
}

void command(sf::Event &event, std::vector<doublePendulum> &p_vec, bool &flag){

    if (event.key.code == sf::Keyboard::Space) {
        if (flag) {
            flag = false;
            for(int k=0; k<NUM_PENDULUM; k++){
                p_vec[k].dtheta1 = 0;
                p_vec[k].dtheta2 = 0;
            }
        }
        else {
            flag = true;
        }
    }
    if (event.key.code == sf::Keyboard::Right && !flag) {
        for(int k=0; k<NUM_PENDULUM; k++){p_vec[k].theta1 += PI/36;}
    }
    if (event.key.code == sf::Keyboard::Left && !flag) {
        for(int k=0; k<NUM_PENDULUM; k++){p_vec[k].theta1 -= PI / 36;}
    }
    if (event.key.code == sf::Keyboard::Up && !flag) {
        for(int k=0; k<NUM_PENDULUM; k++){p_vec[k].theta2 += PI / 36;}
    }
    if (event.key.code == sf::Keyboard::Down && !flag) {
        for(int k=0; k<NUM_PENDULUM; k++){p_vec[k].theta2 -= PI / 36;}
    }
    if (event.key.code == sf::Keyboard::R) {
        for(int k=0; k<NUM_PENDULUM; k++){
            //pendulumGraphic_vec[k].trail.clear();
            p_vec[k].theta1 = 0;
            p_vec[k].theta2 = 0;
            p_vec[k].dtheta1 = 0;
            p_vec[k].dtheta2 = 0;
        }
        flag = false;
    }

};

void graphic(sf::RenderWindow &window,  doublePendulumGraphic &pG, doublePendulum p, float time, bool flag){

    sf::Color circle1;
    sf::Color circle2;
    sf::Color line1;
    sf::Color line2;
    sf::Color trace;
    sf::Vertex vert[2];

    float opacity = 1;

    if (flag) {
        pG.trail.push_back(sf::Vector2f(p.p1x, p.p1y));
    }
    if ((int)pG.trail.size() > TRAILSIZE && TRAILSIZE != 0) {
        pG.trail.erase(pG.trail.begin());
    }

    if(time>TIMESHADE){
        opacity = std::max(0.0f, 1.0f - (time-TIMESHADE) / 10.0f);
    }

    //circle1 = pG.circle1.getFillColor();
    circle2 = pG.circle2.getFillColor();
    line1 = pG.line1.getFillColor();
    line2 = pG.line2.getFillColor();
    trace = pG.traceColor;

    //circle1.a = static_cast<sf::Uint8>(255 * opacity);
    circle2.a = static_cast<sf::Uint8>(255 * opacity);
    line1.a = static_cast<sf::Uint8>(255 * opacity);
    line2.a = static_cast<sf::Uint8>(255 * opacity);
    trace.a = static_cast<sf::Uint8>(255 * opacity);
    
    //pG.circle1.setFillColor(circle1);
    pG.circle2.setFillColor(circle2);
    pG.line1.setFillColor(line1);
    pG.line2.setFillColor(line2);
    pG.traceColor = trace;

    pG.circle1.setPosition(p.p0x, p.p0y);
    pG.circle2.setPosition(p.p1x, p.p1y);
    pG.line1.setPosition(WINDOW_Ox, WINDOW_Oy);
    pG.line2.setPosition(p.p0x, p.p0y);
    pG.line1.setRotation(90-pG.deg1);
    pG.line2.setRotation(90-pG.deg2);
    
    
    if (pG.trail.size() > 1) {
        for (int i = 0; i < (int)pG.trail.size() - 1; i++) {
            vert[0] = sf::Vertex(pG.trail[i], trace);
            vert[1] = sf::Vertex(pG.trail[i + 1], trace);
            window.draw(vert, 2, sf::Lines);
        }
    }
    
    window.draw(pG.line1);
    window.draw(pG.line2);
    window.draw(pG.circle1);
    window.draw(pG.circle2);
}
