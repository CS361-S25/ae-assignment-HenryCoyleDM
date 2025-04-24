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

/*
AEAnimate is an instance of this ALife simulation. It simulates a mammoth steppe ecosystem, featuring grass, mammoths,
and trees. It sets up and maintains a MammothSteppe object, which is the simulation's world
*/
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
        doc << GetDescriptiveText();
        // set the world size and let it handle the toroidal structure
        world.Resize(10, 10);
        world.SetPopStruct_Grid(num_w_boxes, num_h_boxes);
        // add starting organisms to the world: 5 grasses, 1 mammoth, and 1 tree, at arbitrary locations
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
        // give the first mammoth enough energy to navigate to some grass
        first_mammoth->points = 9.8;
        world.AddOrgAt(first_mammoth, 55);
        Tree* first_tree = new Tree();
        world.AddOrgAt(first_tree, 378);
        /* Organism* first_organism = new Organism();
        world.AddOrgAt(first_organism, 0); */
        
    }

    /*
    Updates the world and paints the new cells
    */
    public:
    void DoFrame() override {
        canvas.Clear();
        generation++;
        if (generation > 1) {
            world.Update();
        }
        PaintAllSquares();
    }

    /*
    Paints all of the cells in the world onto the canvas
    */
    private:
    void PaintAllSquares() {
        for (int x=0; x<num_w_boxes; x++) {
            for (int y=0; y<num_h_boxes; y++) {
                PaintSquareIfOccupied(x, y);
            }
        }
    }

    /*
    Paints the single cell (x, y) onto the canvas in the appropriate color
    */
    private:
    void PaintSquareIfOccupied(int x, int y) {
        DrawRect(x, y, GetSquareColor(x, y));
    }

    /*
    Gets the color of a cell: white if empty, otherwise depends on the organism that's in that cell
    */
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

    /*
    Draw a rectangular cell on the canvas at the position corresponding to (x, y) in the world
    */
    private:
    void DrawRect(int x, int y, std::string color) {
        canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, color, "black");
    }

    /*
    Some descriptive text about the Mammoth Steppe ecosystem that can be displayed on the webpage
    */
    private:
    std::string GetDescriptiveText() {
        return "The mammoth steppe was an incredibly biodiverse and productive ecosystem that spanned Eurasia and North America\n\
                at the end of the last glacial maximum. It featured large swaths of grassland and megafauna like wolly\n\
                mammoths. The low albedo of the grass kept the whole planet cooler, keeping Earth in the last glacial maximum.\n\
                Mammoths were responsible for trampling trees and saplings to protect the grasslands from the encroach of\n\
                boreal forests, which have low productivity and high albedo. However, when the mammoths went extinct, very\n\
                possibly by humans, the forests encroached on the grasslands, destroying the mammoth steppe and creating the\n\
                now massive tundras of Eurasia and North America. The higher albedo of the tundras increased global temperatures\n\
                and its low productivity hampered the production of permafrost, bringing Earth out of the last glacial maximum.\n\
                While the mammoth steppe existed, therefore, the grasses and mammoths created a symboitic relationship to defend\n\
                this ecosystem against trees, which is what this simulation depicts. Mammoths are colored red, grasses green,\n\
                and trees blue. Like in the mammoth steppe, mammoths trample trees and eat grass, while the trees slowly take\n\
                over land.";
    }
};

// create an instance of the animator and start running it
AEAnimate animator;

int main() {
    animator.Step();
}