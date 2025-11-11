/*
author : Buyandelger.J
date : 12/11/2025 01:24
title : Binary search algorithm
*/

#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <chrono>
#include <iomanip>
using namespace std;
using namespace chrono;

struct Node
{
    int data;    //
    Node *left;  // Модны зүүн утга
    Node *right; // Модны баруун утга
    Node(int value)
    {
        data = value;
        left = right = nullptr; // анхнаас нь хоосон гэж үзвэл программ дээр алдаа гарахгүй
    }
};

Node *insert(Node *root, int value)
{ // Мод-руу утга нэмэх функц
    // утга нэмэх үед мод нь дэд root болгон нь зүүнээсээ их болон баруунаасаа бага байх ёстой.
    if (root == nullptr)
        return new Node(value); // root хоосон бол шинэ Node үүсгэнэ
    if (root->data > value)
        root->left = insert(root->left, value); // орж ирж буй утга дэд root-ээсээ бага байвал зүүн
    else if (root->data < value)
        root->right = insert(root->right, value); // орж ирж буй утга дэд root-ээсээ их байвал баруун
    return root;
}

void inOrder(Node *root)
{
    /*
    inOrder дараалал нь Binary Search Tree (BST)-ийн хувьд зөв буюу утгуудыг өсөх дарааллаар хэвлэдэг.
    Энэхүү дараалал нь (зүүн → root → баруун) гэсэн хэлбэртэй.
    "in" гэдэг нь root нь дунд буюу дотроо байрладаг гэж санаарай.
    */
    if (root == nullptr)
        return;
    inOrder(root->left);
    cout << root->data << " ";
    inOrder(root->right);
}

/*
Binary search нь O(log n) хурдтай тухайн бүтцээс дата хайдаг ба үүгээрээ алдартай.
Яаж хэрхэн ажилдаг вэ гэдэг нь :
    1-1000 хүртэл тоо байлаа гэж бодоход тухайн хамгийн бага ба хамгийн их тооны
    голын тооноос нь эхэлж хайлт хийдэг ба хэрнээ хайж буй утга нь голын тооноос
    их бол бүтцийн баруун тал-руу харин бага бол бүтцийн зүйл тал-руу явдаг.
    Тийм тул Recursive function буюу өөрийгөө дахин дахин дууддаг үйлдэл
    хэрэгжүүлэх хэрэгтэй. (min + max) / 2 гэдэг үйлдэл давтагдаж байгаа тул
*/
bool binary_Search(Node *root, int key)
{
    if (root == nullptr)
        return false;
    if (root->data == key) // хайж буй утгаа олох юм бол True буцаана
        return true;
    if (root->data > key)                      // хайж буй утга нь root-аас бага бол зүүн дэд мод руу
        return binary_Search(root->left, key); // Recursive function
    else                                       // хайж буй утга нь root-аас их бол баруун дэд мод руу
        return binary_Search(root->right, key);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(time(0));
    auto start = high_resolution_clock::now();
    Node *root = nullptr;
    cout << "10 ширхэг тоо оруулж байна\n";
    // 10 ширхэг санамсаргүй тоо үүсгэн BST-д нэмэх
    for (int i = 0; i < 10; i++)
    {
        int num = rand() % 100 + 1;
        cout << num << " ";
        root = insert(root, num);
    }
    inOrder(root);
    cout << "\n";
    int target = rand() % 100 + 1;
    if (binary_Search(root, target))
        cout << "✅ Олсон\n";
    else
        cout << "❌ Олдсонгүй\n";
    auto end = high_resolution_clock::now();
    auto elapsed = duration_cast<microseconds>(end - start);
    cout << fixed << setprecision(7);
    cout << "Нийт гүйцэтгэсэн хугацаа " << elapsed.count() << " микросекунд\n";
    return 0;
}