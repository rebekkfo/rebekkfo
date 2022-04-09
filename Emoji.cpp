#include "Emoji.h"

//tomt gult fjes
void Face::draw(AnimationWindow& win) {
    win.draw_circle(centre, radius, Color::yellow);
}

//kosnktruktør EmptyFace
EmptyFace::EmptyFace(Point c, int r) : Face{c, r}, 
            leftEyePosition{c.x - 20, c.y - 5},
            rightEyePosition{c.x + 20, c.y - 5},
            eyeRadius{10} {}

void EmptyFace::draw(AnimationWindow& win) {
    Face::draw(win);
    win.draw_circle(leftEyePosition, eyeRadius, Color::black);
    win.draw_circle(rightEyePosition, eyeRadius, Color::black);
}

SmilingFace::SmilingFace(Point centre, int radius) : EmptyFace{centre, radius} {
    mouthPosition = {centre.x, centre.y + 10};
    mouthWidth = 60;
    mouthHeight = 40;
    mouthStartAngle = 180;
    mouuthEndAngle = 360;
}

void SmilingFace::draw(AnimationWindow& win) {
    EmptyFace::draw(win);
    win.draw_arc(mouthPosition, mouthWidth, mouthHeight, mouthStartAngle, mouuthEndAngle, Color::black);
}

SurprisedFace::SurprisedFace(Point c, int r) : SmilingFace{c, r} {
    mouthHeight = 20;
    mouthPosition = {mouthPosition.x, mouthPosition.y + 20};
    mouthStartAngle = 0;
}

SadFace::SadFace(Point c, int r) : EmptyFace{c, r} {}

void SadFace::draw(AnimationWindow& win) {
    EmptyFace::draw(win);
    win.draw_arc({centre.x, centre.y + 30}, 60, 40, 0, 180, Color::black);
}

AngryFace::AngryFace(Point c, int r) : EmptyFace{c, r} {}

void AngryFace::draw(AnimationWindow& win) {
    EmptyFace::draw(win);

    const Point mouthPosition = Point{centre.x - 60 / 2, centre.y + 10};
    win.draw_rectangle(mouthPosition, 60, 20, Color::white);
    for (int i = -25; i < 25; i += 10) {
        win.draw_line(Point{centre.x - i, mouthPosition.y}, Point{centre.x - i, mouthPosition.y + 19}, Color::black);
    }

    win.draw_line(Point{centre.x - 20, centre.y - 20}, Point{centre.x - 5, centre.y - 10}, Color::black);
	win.draw_line(Point{centre.x + 20, centre.y - 20}, Point{centre.x + 5, centre.y - 10}, Color::black);

}

NeutralFace::NeutralFace(Point c, int r) : EmptyFace {c, r} {}

void NeutralFace::draw(AnimationWindow& win) {
    EmptyFace::draw(win);
    win.draw_line(Point{centre.x - 30, centre.y + 10}, Point{centre.x + 30, centre.y + 10}, Color::black);
}

WinkFace::WinkFace(Point c, int r) : Face{c, r} {}

void WinkFace::draw(AnimationWindow& win) {
    Face::draw(win);
    win.draw_circle(Point{centre.x - 20, centre.y - 5}, 10, Color::black);
    win.draw_arc(Point{centre.x + 25, centre.y}, 20, 20, 0, 160, Color::black);
    win.draw_arc(Point{centre.x, centre.y + 10}, 60, 40, 180, 360, Color::black);

}
