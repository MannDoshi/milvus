#include <vector>
#include <iostream>
#include<algorithm>
using namespace std;

// Counting Inversion : BIT Implementation
int getSum(int BITree[], int index)
{
    int sum = 0; 
    while (index > 0)
    {
        sum += BITree[index];
        index -= index & (-index);
    }
    return sum;
}
 
void updateBIT(int BITree[], int n, int index, int val)
{
    while (index <= n)
    {
        BITree[index] += val;
        index += index & (-index);
    }
}
 
int getInvCount(vector<int> arr)
{
    int n = arr.size();
    int invcount = 0; 
    int maxElement = 0;
    for (int i=0; i<n; i++)
        if (maxElement < arr[i])
            maxElement = arr[i];
 
    int BIT[maxElement+1];
    for (int i=1; i<=maxElement; i++)
        BIT[i] = 0;
 
    for (int i=n-1; i>=0; i--)
    {
        invcount += getSum(BIT, arr[i]-1);
        updateBIT(BIT, maxElement, arr[i], 1);
    }
 
    return invcount;
}
   
struct vec_with_index{
    float value;
    unsigned short int index;
    vec_with_index(float value,int index){
        this->value = value;
        this->index = index;
    }
};

// comparator for sorting to provide ranks to elements
bool comparator(const vec_with_index& lhs, const vec_with_index& rhs) {
   return lhs.value < rhs.value;
}

float kendall_tau_distance(float *va, float *vb, size_t n){
    vector<vec_with_index> vi_a;
    vector<vec_with_index> vi_b;
    vector<int> I(n);
    for(int i=0;i<n;i++){
        vi_a.push_back(vec_with_index(va[i],i));
        vi_b.push_back(vec_with_index(vb[i],i));
    }
    
    std::sort(vi_a.begin(), vi_a.end(), &comparator);
    std::sort(vi_b.begin(), vi_b.end(), &comparator);

    size_t i = 0;
    while(i<n){
        int k = i;
        I[vi_a[i].index] = vi_b[i].index+1;
        while((k<vi_a.size()-1)&&(vi_a[k].value==vi_a[k+1].value)){
            if(vi_b[k].value!=vi_b[k+1].value){
                cout<<"Value Error : Number of duplicate items not equal"<<endl;
                return -1;
            }
            I[vi_a[k+1].index] = vi_b[k+1].index+1;
            k+=1;
        }
        i += (k-i+1);
    }
    // for calculating inversions via BIT implementation
    return 2*(float(getInvCount(I)))/(n*(n-1));
}

int main(){
    float va[]={90,100,200,300,100};
    float vb[]={0,1,2,4,5};
    float r;
    r = kendall_tau_distance(va,vb,5);
    cout<<r<<endl;
    return 0;
}