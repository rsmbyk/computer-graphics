#ifndef COMPUTER_GRAPHICS_CAR_HPP
#define COMPUTER_GRAPHICS_CAR_HPP

#include <vector>
#include <customs/shapes/Box.hpp>

class Car : public Object {
public:
    Car (GLfloat x, GLfloat y, GLfloat z, GLfloat size);
    
    void render () override;
    void clean () override;
    void move (int coord, GLfloat amount) override;
    void rotate (GLfloat x, GLfloat y, GLfloat z) override;
    void scale (GLfloat x, GLfloat y, GLfloat z) override;
    
    static constexpr GLfloat multiplier = 0.1f;

private:
    Box *box, *connector;
    std::vector<Object*> windows {};
};

#endif // COMPUTER_GRAPHICS_CAR_HPP
