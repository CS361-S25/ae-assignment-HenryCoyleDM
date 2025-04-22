#include "emp/math/Random.hpp"
#include "emp/web/Animate.hpp"
#include "emp/web/web.hpp"

#include "MammothSteppe.h"
#include "Organism.h"
#include "Mammoth.h"
#include "Grass.h"

// document for displaying stuff
emp::web::Document doc{"target"};

class AEAnimate : public emp::web::Animate {
    // the size of the world in cells
    const int num_h_boxes = 10;
    const int num_w_boxes = 10;
    // the size in pixels of one cell
    const double RECT_SIDE = 10;
    // the size in pixels of the grid
    const double width{num_w_boxes * RECT_SIDE};
    const double height{num_h_boxes * RECT_SIDE};
    // random number generator for all random processes
    emp::Random random{5};
    // canvas for painting
    emp::web::Canvas canvas{width, height, "canvas"};
    // world
    MammothSteppe world{&random};

    public: AEAnimate() {
        // add canvas to document
        doc << canvas;
        // add control buttons to document
        doc << GetToggleButton("Toggle");
        doc << GetStepButton("Step");
        // set the world size and let it handle the toroidal structure
        world.Resize(10, 10);
        world.SetPopStruct_Grid(num_w_boxes, num_h_boxes);
        // add starting organisms for the two species to the world
        Mammoth first_mammoth;
        world.AddOrgAt(&first_mammoth, 1);
        // world.Inject(*first_mammoth);
        Grass first_grass;
        world.AddOrgAt(&first_grass, 0);
    }

    public:
    void DoFrame() override {
        canvas.Clear();
        for (int x=0; x<num_w_boxes; x++) {
            for (int y=0; y<num_h_boxes; y++) {
                PaintSquareIfOccupied(x, y);
            }
        }
    }

    private:
    void PaintSquareIfOccupied(int x, int y) {
        if (world.IsOccupied(y * num_w_boxes + x)) {
            emp::Ptr<Organism> organism_at = world.GetOrgPtr(y * num_w_boxes + x);
            std::cout << "cell index is " << std::to_string(y * num_w_boxes + x) << std::endl;
            std::cout << "cell " << std::to_string(x) << ", " << std::to_string(y) << " has an organism\n";
            std::string color_at = organism_at->GetColor();
            DrawRect(x, y, color_at);
        } else {
            std::cout << "cell " << std::to_string(x) << ", " << std::to_string(y) << " is empty\n";
            DrawRect(x, y, "white");
        }
    }

    private:
    void DrawRect(int x, int y, std::string color) {
        canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, color, "black");
    }
};

AEAnimate animator;

int main() {
    animator.Step();
}