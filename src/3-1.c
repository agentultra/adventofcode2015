#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct binary_node {
  int x, y;
  struct binary_node* left;
  struct binary_node* right;
} binary_node;

void free_binary_node(binary_node* t) {
  if (t != 0) {
    free_binary_node(t->left);
    free_binary_node(t->right);
    free(t);
  }
}

bool point_lt(int x1, int y1, int x2, int y2) {
  if ((x1 < x2) || (x1 == x2 && y1 <= y2)) {
    return true;
  }
  return false;
}

bool point_gt(int x1, int y1, int x2, int y2) {
  if ((x1 > x2) || (x1 == x2 && y1 >= y2)) {
    return true;
  }
  return false;
}

void insert(binary_node** tree, int x, int y) {
  if (*tree == 0) {
    *tree = (binary_node*) malloc(sizeof(binary_node));
    (*tree)->x = x;
    (*tree)->y = y;
    (*tree)->left = 0;
    (*tree)->right = 0;
  }
  else if (point_lt(x, y, (*tree)->x, (*tree)->y)) {
    insert(&(*tree)->left, x, y);
  }
  else if (point_gt(x, y, (*tree)->x, (*tree)->y)) {
    insert(&(*tree)->right, x, y);
  }
}

bool search(binary_node** tree, int x, int y) {
  if ((*tree)->x == x && (*tree)->y == y) {
    return true;
  }
  else if (point_lt(x, y, (*tree)->x, (*tree)->y) && (*tree)->left != 0) {
    return search(&(*tree)->left, x, y);
  }
  else if (point_gt(x, y, (*tree)->x, (*tree)->y) && (*tree)->right != 0) {
    return search(&(*tree)->right, x, y);
  }
  else {
    return false;
  }
}

int main(int argc, char** argv) {
  FILE* input = fopen("3-1.txt", "r");
  if (!input) {
    perror("Error opening input file!");
    exit(EXIT_FAILURE);
  }

  binary_node *tree = 0;
  int x = 0, y = 0;
  insert(&tree, x, y);
  int total_presents_delivered = 1;
  char line_buffer[512];
  while (fgets(line_buffer, sizeof line_buffer, input) != NULL) {
    char* buf = line_buffer;
    while(*buf) {
      switch (*buf) {
      case '<':
        x--;
        break;
      case '>':
        x++;
        break;
      case '^':
        y--;
        break;
      case 'v':
        y++;
        break;
      }
      if (!search(&tree, x, y)) {
        insert(&tree, x, y);
        total_presents_delivered++;
      }
      ++buf;
    }
  }
  free_binary_node(tree);

  if (ferror(input)) {
    perror("Error reading input line");
    fprintf(stderr, "fgets() failed in file %s at line %d\n", __FILE__, __LINE__);
    exit(EXIT_FAILURE);
  }

  printf("Santa delivered %d presents\n", total_presents_delivered);
}
