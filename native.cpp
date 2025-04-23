#include "emp/math/Random.hpp"

#include "MammothSteppe.hpp"
#include "Organism.hpp"

// This is the main function for the NATIVE version of this project.



int main(int argc, char* argv[])
{
  // the size of the world in cells
  int num_h_boxes = 10;
  int num_w_boxes = 10;
  // the size in pixels of one cell
  double RECT_SIDE = 10;
  // the size in pixels of the grid
  double width = num_w_boxes * RECT_SIDE;
  double height = num_h_boxes * RECT_SIDE;
  // the first frame is generation 1
  int generation = 0;
  // random number generator for all random processes
  emp::Random random = *new emp::Random(5);
  // world
  MammothSteppe world(&random);
  // set the world size and let it handle the toroidal structure
  world.Resize(10, 10);
  world.SetPopStruct_Grid(num_w_boxes, num_h_boxes);
  // add starting organisms for the two species to the world
  /* Grass* first_grass = new Grass(&world, 0, &random);
  world.AddOrgAt(first_grass, 0);
  Mammoth* first_mammoth = new Mammoth(&world, 1, &random);
  world.AddOrgAt(first_mammoth, 1); */
  Organism* first_organism = new Organism(world, 0, &random);
  world.AddOrgAt(first_organism, 0);
  for (int i = 0; i < 5; i++) {
    world.Update();
  }
}
