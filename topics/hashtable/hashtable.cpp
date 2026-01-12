#include "hashtable.h"
#include <iostream>

using namespace std;

void printStudent(struct Student *s)
{
  cout << s->id << " " << s->fname << " " << s->lname << " " << s->major << " " << s->level << " " << s->gpa << endl;
}

void printList(struct Student *l)
{
  cout << "#Students (" << length(l) << "):" << "\n";
  while (l != NULL)
  {
    cout << "#\t - ";
    printStudent(l);
    l = l->next;
  }
}

void printHash(Student **hasharray, int size)
{
  for (int i = 0; i < size; i++)
  {
    if (hasharray[i] == NULL)
      continue;
    cout << "#" << i << endl;
    printList(hasharray[i]);
  }
}

void makeEmpty(Student *l)
{
  Student *ptr;
  while (l != NULL)
  {
    ptr = l->next;
    l->level = 0;
    l->gpa = 0;
    l->next = NULL;
    delete l;
    l = ptr;
  }
}

Student *find(Student *l, string id)
{
  while (l != NULL)
  {
    if (l->id == id)
      return l;
    l = l->next;
  }
  return NULL;
}

int findI(Student *l, string id)
{
  int i = 0;
  while (l != NULL)
  {
    if (l->id == id)
      return i;
    i++;
    l = l->next;
  }
  return -1;
}

int hashf(string id)
{
  // id => ##C#CCC####
  unsigned long h = 0;
  for (char c : id)
  {
    h = h * 31 + static_cast<unsigned char>(c); // polynomial rolling
  }
  return static_cast<int>(h % 10000);
}

void hashInsert(Student **hasharray, Student *l)
{
  if (l == NULL)
    return;
  int idx = hashf(l->id);
  l->next = hasharray[idx];
  hasharray[idx] = l;
}

void hashInsert(Student **hasharray, string id, string fname, string lname, string major, int level, float gpa)
{
  Student *t = new Student;
  t->id = id;
  t->fname = fname;
  t->lname = lname;
  t->major = major;
  t->gpa = gpa;
  t->level = level;
  hashInsert(hasharray, t);
}

Student *search(Student **hasharray, string id)
{
  int idx = hashf(id);
  return find(hasharray[idx], id);
}

void hashRemove(Student **hasharray, string id)
{
  int idx = hashf(id);
  removeById(&hasharray[idx], id);
}

void remove(Student **l, int j)
{
  if (l == NULL || *l == NULL)
    return;
  if (j <= 0)
  {
    Student *tmp = *l;
    *l = tmp->next;
    tmp->next = NULL;
    delete tmp;
    return;
  }
  Student *cur = *l;
  Student *prev = NULL;
  int i = 0;
  while (cur != NULL && i < j)
  {
    prev = cur;
    cur = cur->next;
    i++;
  }
  if (cur == NULL)
    return;
  prev->next = cur->next;
  cur->next = NULL;
  delete cur;
}

void removeById(Student **l, string id)
{
  int j = findI(*l, id);
  if (j > -1)
  {
    remove(l, j);
  }
}

struct Student *findKth(Student *l, int k)
{
  if (k < 0)
    return NULL;
  int i = 0;
  while (l != NULL)
  {
    if (i == k)
      return l;
    i++;
    l = l->next;
  }
  return NULL;
}

int findKthI(Student *l, int k)
{
  if (k < 0)
    return -1;
  int len = 0;
  Student *p = l;
  while (p != NULL)
  {
    len++;
    p = p->next;
  }
  return (k < len) ? k : -1;
}

int length(Student *l)
{
  int c = 0;
  while (l != NULL)
  {
    c++;
    l = l->next;
  }
  return c;
}
