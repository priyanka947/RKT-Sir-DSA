#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int id;
  int in_degree;
  struct Node *next;
} Node;

Node *create_node(int id) {
  Node *node = malloc(sizeof(Node));
  node->id = id;
  node->in_degree = 0;
  node->next = NULL;
  return node;
}

void add_edge(Node *nodes[], int from, int to) {
  Node *node = nodes[from];
  while (node->next) {
    node = node->next;
  }
  node->next = create_node(to);
  nodes[to]->in_degree++;
}

bool topological_sort(Node *nodes[], int num_tasks, int order[]) {
  int visited[num_tasks];
  int queue[num_tasks];
  int head = 0;
  int tail = 0;
  int order_index = 0;

  for (int i = 0; i < num_tasks; i++) {
    visited[i] = 0;
  }

  for (int i = 0; i < num_tasks; i++) {
    if (nodes[i]->in_degree == 0) {
      queue[tail++] = i;
      visited[i] = 1;
    }
  }

  while (head != tail) {
    int current = queue[head++];
    order[order_index++] = current;

    Node *neighbor = nodes[current]->next;
    while (neighbor) {
      neighbor->in_degree--;
      if (neighbor->in_degree == 0 && !visited[neighbor->id]) {
        queue[tail++] = neighbor->id;
        visited[neighbor->id] = 1;
      }
      neighbor = neighbor->next;
    }
  }

  return order_index == num_tasks;
}

int main() {
  int num_tasks;
  int num_prerequisites;

  // Read the number of tasks and prerequisites
  scanf("%d %d", &num_tasks, &num_prerequisites);

  // Create nodes
  Node *nodes[num_tasks];
  for (int i = 0; i < num_tasks; i++) {
    nodes[i] = create_node(i);
  }

  // Read the prerequisites and add edges
  for (int i = 0; i < num_prerequisites; i++) {
    int from, to;
    scanf("%d %d", &from, &to);
    add_edge(nodes, from, to);
  }

  // Perform topological sort and store the order
  int order[num_tasks];
  bool success = topological_sort(nodes, num_tasks, order);

  // Check for cycles
  if (!success) {
    printf("There is a cycle in the task dependencies. It is impossible to finish all tasks.\n");
    return 1;
  }

  // Print the ordering of tasks
  printf("One possible ordering of tasks:\n");
  for (int i = 0; i < num_tasks; i++) {
    printf("%d ", order[i]);
  }
  printf("\n");

  return 0;
}
