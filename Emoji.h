#pragma once
#include "AnimationWindow.h"

// Abstrakt klasse. Arvende konkrete klasser må implementere funksjonen draw()
// som tegner former i vinduet de skal bli vist i.
class Emoji {
public:
    virtual void draw(AnimationWindow&) = 0;
    virtual ~Emoji(){}; //destruktør
};

class Face : public Emoji {
public:
    virtual void draw(AnimationWindow& win) override = 0;
    Face(Point c, int r) : centre{c}, radius{r} {};
protected:
    Point centre{0,0};
    int radius = 0;
};

class EmptyFace : public Face {
public:
    EmptyFace(Point c, int r);
    void draw(AnimationWindow& win) override;
private:
    Point leftEyePosition{0, 0};
    Point rightEyePosition{0, 0};
    int eyeRadius = 0;
};

class SmilingFace : public EmptyFace {
public:
    SmilingFace(Point c, int r);
    void draw(AnimationWindow& win) override;
protected:
    Point mouthPosition {0, 0};
    int mouthWidth = 0;
    int mouthHeight = 0;
    int mouthStartAngle = 0;
    int mouuthEndAngle = 0;
};

//nb eksmepel på dårlig kode
class SurprisedFace : public SmilingFace {
public:
    SurprisedFace(Point c, int r);
    /*ikke arv fra SmilingFace, selv om det virker fornuftig siden man slipper å 
    tegne mouth på nytt og definere draw(). Skal ikke arve fra en klasse bare for å 
    slippe å redefinere ting, skaper avhengighet mellom surprised og smiling face. 
    Endring av smiling face vil også endre surprised face, og det er bare ønskelig hvis
    surprised face "er en type smiling face", og det er det ikke.*/
};

class SadFace : public EmptyFace {
public:
    SadFace(Point c, int r);
    void draw(AnimationWindow& win) override;
};

class AngryFace : public EmptyFace {
public:
    AngryFace(Point c, int r);
    void draw(AnimationWindow& win) override;
};

class NeutralFace : public EmptyFace {
public:
    NeutralFace(Point c, int r);
    void draw(AnimationWindow& win) override;
};

class WinkFace : public Face {
public:
    WinkFace(Point c, int r);
    void draw(AnimationWindow& win) override;
};

