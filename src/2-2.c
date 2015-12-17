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

int ribbon_order_length(const right_rect_prism* r) {
  int face_perimeters[3] = {(r->l * 2) + (r->w * 2),
                            (r->l * 2) + (r->h * 2),
                            (r->w * 2) + (r->h * 2)};
  int bow = r->l * r->w * r->h;

  int smallest = face_perimeters[0];
  for (int i = 1; i < 3; i++) {
    if (face_perimeters[i] < smallest) {
      smallest = face_perimeters[i];
    }
  }

  return smallest + bow;
}

int main(int argc, char** argv) {
  FILE* input = fopen("2-1.txt", "r");
  if (!input) {
    perror("Error opening input file!");
    exit(EXIT_FAILURE);
  }

  int total_ribbon_length = 0;
  char line_buffer[512];
  while (fgets(line_buffer, sizeof line_buffer, input) != NULL) {
    right_rect_prism r = rect_prism_from_str(line_buffer);
    total_ribbon_length += ribbon_order_length(&r);
  }

  if (ferror(input)) {
    perror("Error reading input line");
    fprintf(stderr, "fgets() failed in file %s at line %d\n", __FILE__, __LINE__);
    exit(EXIT_FAILURE);
  }

  printf("Order %d feet of ribbon\n", total_ribbon_length);
}
