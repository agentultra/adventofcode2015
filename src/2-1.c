#include <stdio.h>
#include <stdlib.h>

typedef struct right_rect_prism {
  int l, w, h;
} right_rect_prism;

right_rect_prism rect_prism_from_str(char* s) {
  int l, w, h;
  int ret = sscanf(s, "%dx%dx%d", &l, &w, &h);

  if (ret) {
    return (right_rect_prism){.l = l, .w = w, .h = h};
  }

  return (right_rect_prism){.l = 0, .w = 0, .h = 0};
}

int wrapping_area(const right_rect_prism* r) {
  int side_areas[3] = {r->l * r->w,
                       r->w * r->h,
                       r->h * r->l};

  int total = 0;
  int smallest = side_areas[0];
  for (int i = 0; i < 3; i++) {
    if (side_areas[i] < smallest) {
      smallest = side_areas[i];
    }
    total += 2 * side_areas[i];
  }

  return total + smallest;
}

int main(int argc, char** argv) {
  FILE* input = fopen("2-1.txt", "r");
  if (!input) {
    perror("Error opening input file!");
    return EXIT_FAILURE;
  }

  int total_area = 0;
  char line_buffer[512];
  while (fgets(line_buffer, sizeof line_buffer, input) != NULL) {
    right_rect_prism r = rect_prism_from_str(line_buffer);
    total_area += wrapping_area(&r);
  }
  printf("Order %d square feet\n", total_area);

  if (ferror(input)) {
    perror("Error reading input line");
    fprintf(stderr, "fgets() failed in file %s at line %d\n", __FILE__, __LINE__);
    exit(EXIT_FAILURE);
  }
}
