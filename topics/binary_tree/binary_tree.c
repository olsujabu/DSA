// author : Buyandelger.J
// title :  Binary Tree
#include "binary_tree.h"
#include <stdio.h>

void add(Tree *tree, int a)
{
  if (tree->nodes < 100)
  {
    tree->values[tree->nodes] = a;
    tree->nodes++;
  }
}

int nodeLoc(Tree *tree, int val)
{
  for (int i = 0; i < tree->nodes; i++)
  {
    if (tree->values[i] == val)
    {
     return i;
    }
  }
  return -1;
}

void preorder(Tree *tree, int val) // root -> left -> right
{
  int loc = nodeLoc(tree, val);
  if (loc < 0 || loc >= tree->nodes)
  {
    return;
  }
  printf("%d ", tree->values[loc]);
  int left = 2 * loc + 1;
  int right = 2 * loc + 2;
  if (left < tree->nodes)
    preorder(tree, tree->values[left]);
  if (right < tree->nodes)
    preorder(tree, tree->values[right]);
}

int root(Tree *tree)
{
  return tree->values[0];
}

void inorder(Tree *tree, int val) // left -> root -> right
{
  int loc = nodeLoc(tree, val);
  if (loc < 0 || loc >= tree->nodes)
    return;
  int left = 2 * loc + 1;
  int right = 2 * loc + 2;
  if (left < tree->nodes)
    inorder(tree, tree->values[left]);
  printf("%d ", tree->values[loc]);
  if (right < tree->nodes)
    inorder(tree, tree->values[right]);
}

void postorder(Tree *tree, int val) // left -> right -> root
{
  int loc = nodeLoc(tree, val);
  if (loc < 0 || loc >= tree->nodes)
    return;
  int left = loc * 2 + 1;
  int right = loc * 2 + 2;
  if (left < tree->nodes)
    postorder(tree, tree->values[left]);
  if (right < tree->nodes)
    postorder(tree, tree->values[right]);
  printf("%d ", tree->values[loc]);
}

int height(Tree *tree, int val)
{
  int loc = nodeLoc(tree, val);
  if (loc < 0)
    return 0;
  int left = 2 * loc + 1;
  int right = 2 * loc + 2;
  int hl = 0, hr = 0;
  if (left < tree->nodes)
    hl = height(tree, tree->values[left]);
  if (right < tree->nodes)
    hr = height(tree, tree->values[right]);
  return 1 + (hl > hr ? hl : hr);
}

int level(Tree *tree, int val)
{
  int loc = nodeLoc(tree, val);
  if (loc < 0)
    return -1;
  int level = 0;
  while (loc > 0)
  {
    loc = (loc - 1) / 2;
    level++;
  }
  return level;
}

int sibling(Tree *tree, int val)
{
  int loc = nodeLoc(tree, val);
  if (loc <= 0)
    return -1;
  int parent = (loc - 1) / 2;
  int left = 2 * parent + 1;
  int right = 2 * parent + 2;

  if (left < tree->nodes && tree->values[left] == val && right < tree->nodes)
    return right;
  if (right < tree->nodes && tree->values[right] == val && left < tree->nodes)
    return left;
  return -1;
}

int parent(Tree *tree, int val)
{
  int loc = nodeLoc(tree, val);
  if (loc <= 0)
    return -1;
  return (loc - 1) / 2;
}

void parents(Tree *tree, int val)
{
  int loc = nodeLoc(tree, val);
  while (loc > 0)
  {
    loc = (loc - 1) / 2;
    printf("%d ", tree->values[loc]);
  }
}