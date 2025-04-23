#include "emp/math/Random.hpp"
#include "emp/web/Animate.hpp"
#include "emp/web/web.hpp"

#include "MammothSteppe.hpp"
#include "Organism.hpp"
#include "Mammoth.hpp"
#include "Grass.hpp"
#include "Tree.hpp"

// document for displaying stuff
emp::web::Document doc{"target"};

class AEAnimate : public emp::web::Animate {
    // the size of the world in cells
    const int num_h_boxes = 50;
    const int num_w_boxes = 50;
    // the size in pixels of one cell
    const double RECT_SIDE = 10;
    // the size in pixels of the grid
    const double width{num_w_boxes * RECT_SIDE};
    const double height{num_h_boxes * RECT_SIDE};
    // the first frame is generation 1
    int generation = 0;
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
        // add starting organisms to the world: 5 grasses, 1 mammoth, and 1 tree
        Grass* first_grass = new Grass();
        world.AddOrgAt(first_grass, 0);
        Grass* second_grass = new Grass();
        world.AddOrgAt(second_grass, 1340);
        Grass* third_grass = new Grass();
        world.AddOrgAt(third_grass, 2378);
        Grass* fourth_grass = new Grass();
        world.AddOrgAt(fourth_grass, 888);
        Grass* fifth_grass = new Grass();
        world.AddOrgAt(fifth_grass, 245);
        Mammoth* first_mammoth = new Mammoth();
        world.AddOrgAt(first_mammoth, 55);
        Tree* first_tree = new Tree();
        world.AddOrgAt(first_tree, 378);
        /* Organism* first_organism = new Organism();
        world.AddOrgAt(first_organism, 0); */
        
    }

    public:
    void DoFrame() override {
        canvas.Clear();
        generation++;
        if (generation > 1) {
            world.Update();
        }
        PaintAllSquares();
    }

    private:
    void PaintAllSquares() {
        for (int x=0; x<num_w_boxes; x++) {
            for (int y=0; y<num_h_boxes; y++) {
                PaintSquareIfOccupied(x, y);
            }
        }
    }

    private:
    void PaintSquareIfOccupied(int x, int y) {
        DrawRect(x, y, GetSquareColor(x, y));
    }

    private:
    std::string GetSquareColor(int x, int y) {
        int world_index = y * num_w_boxes + x;
        if (world.IsOccupied(world_index)) {
            emp::Ptr<Organism> organism_at = world.GetOrgPtr(world_index);
            // std::cout << "Getting organism color\n";
            return organism_at->GetColor();
        } else {
            // empty cells are white
            return "rgb(255, 255, 255)";
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