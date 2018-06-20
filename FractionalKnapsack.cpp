#include <iostream>
#include <algorithm>
using namespace std;
class Item
{
public:
    int value, weight;
    void getData(int val, int wt)
    {
        value = val;
        weight = wt;
    }
};
bool cmp(struct Item a, struct Item b)
{
    double r1 = (double)a.value/a.weight;
    double r2 = (double)b.value/b.weight;
    return r1 > r2;
}
double FractionalKnapsack(int W, Item arr[], int n)
{
    sort(arr, arr+n, cmp);
    int curWeight = 0;
    double finalvalue = 0.0;
    for (int i=0; i<n; i++)
    {
        if(curWeight + arr[i].weight <= W)
        {
            curWeight += arr[i].weight;
            finalvalue += arr[i].value;
        }
        else
        {
            int remain = W - curWeight;
            finalvalue += arr[i].value*((double)remain/arr[i].weight);
            break;
        }
    }
    return finalvalue;
}
int main()
{
    int W = 50;
    Item arr[3];
    arr[0].getData(60, 10);
    arr[1].getData(100, 20);
    arr[2].getData(120, 30);
    cout<<"Maximum value we can obtain = "<<FractionalKnapsack(W, arr, 3);
    return 0;
}
