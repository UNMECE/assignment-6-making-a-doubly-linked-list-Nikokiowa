#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "coordinate.h"

using namespace std;


int list_length(Coordinate* list_beginning) {
  int count = 0;
  Coordinate* temp = list_beginning;
  while (temp) {
    count++;
    temp = temp->next;
  }
  return count;

}


// Add coordinate.
void add_coordinate(Coordinate** list_end, float x, float y) {
  Coordinate* new_coord = new Coordinate;
  new_coord->x = x;
  new_coord->y = y;
  new_coord->next = nullptr;
  new_coord->previous = nullptr;

  if (*list_end == nullptr) {
    new_coord->coord_id = 1;
    *list_end = new_coord;
  } else {
    Coordinate* end = *list_end;
    while (end->next != nullptr) end = end->next;
    new_coord->coord_id = list_length(*list_end) + 1;
    end->next = new_coord;
    new_coord->previous = end;
  }
}


// Display coordinate forward.
void forward_display(Coordinate *list_beginning) {
  Coordinate* temp = list_beginning;
  cout << "Coordinates (Forward): " << endl;
  while (temp != nullptr) {
    cout << "ID: " << temp->coord_id << " (x=" << temp->x << ", y=" << temp->y << ")" << endl;
    temp = temp->next;
  }
}


// Display coordinates backward.
void backward_display(Coordinate* list_end) {
  if (!list_end) return;
  Coordinate* temp = list_end;
  while (temp->next != nullptr)
    temp = temp->next;

  cout << "Coordinate (Backwards):" << endl;
  while (temp != nullptr) {
    cout << "ID: " << temp->coord_id << " (x=" << temp->x << ", y=" << temp->y << ")" << endl;
    temp = temp->previous;
  }
}


// Delete coordinate.
void delete_coordinate(Coordinate** list_beginning, int coord_id_to_delete) {
  Coordinate* temp = *list_beginning;
  while (temp && temp->coord_id != coord_id_to_delete)
    temp = temp->next;

  if (temp->previous)
    temp->previous->next = temp->next;
  else
    *list_beginning = temp->next;

  if (temp->next)
    temp->next->previous = temp->previous;

  delete temp;
  cout << "Coordinate with ID " << coord_id_to_delete << " deleted." << endl;
}


// Find closest coordinate.
void closest_to(Coordinate* list_beginning, float x, float y) {
  if (!list_beginning) {
    cout << "List is empty." << endl;
    return;
  }

  Coordinate* temp = list_beginning;
  Coordinate* closest = list_beginning;
  float min_dist = sqrt(pow(temp->x - x, 2) + pow(temp->y - y, 2));

  while (temp) {
    float dist = sqrt(pow(temp->x - x, 2) + pow(temp->y - y, 2));
    if (dist < min_dist) {
      min_dist = dist;
      closest = temp;
    }
    temp = temp->next;
  }

  cout << "Closest coordinate to (" << x << ", " << y << ") is ID: " << closest->coord_id << " (x=" << closest->x << ", y=" << closest->y << ") with distance " << min_dist << endl;

}


int main(int argc, char* argv[]) {
  if (argc != 2) {
    cout << "Command usage: ./main (number of coordinates)" << endl; // Give the user an understanding of how to use the command in command line.
    return 1;
  }

  int num = atoi(argv[1]);
  srand(time(0));

  Coordinate* list_beginning = nullptr;
  Coordinate* list_end = nullptr;

  // Generate random coordinates the amount of equal to user input.
  for (int i = 0; i < num; i++) {
    float x = static_cast<float>(rand() % 100);
    float y = static_cast<float>(rand() % 100);
    add_coordinate(&list_beginning, x, y);
  }

  forward_display(list_beginning);
  cout << endl;

  backward_display(list_beginning);
  cout << endl;

  cout << "Deleting coordinate with ID 6 (if it exists)..." << endl;
  delete_coordinate(&list_beginning, 6); // Delete coordinate at ID 6.
  cout << endl;

  forward_display(list_beginning);
  cout << endl;

  cout << "Finding closest coordinate to (50, 50):" << endl;
  closest_to(list_beginning, 50, 50);

  return 0;

}

