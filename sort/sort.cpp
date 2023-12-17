#include <iostream>
#include <fstream>

using namespace std;

#define MAXSIZE 100

typedef struct {
    int ar[MAXSIZE+1];  //ar[0]作哨兵
    int length;
} SqList;

void show(SqList L) {
    for (int i = 1; i <= L.length; i++)
        cout << L.ar[i] << " ";
    cout << endl;
}

//希尔排序
void ShellInsert(SqList &L, int interval) {
    for (int i = interval+1; i <= L.length; i++) {
        if (L.ar[i] < L.ar[i-interval]) {   //满足条件才继续，不然就是原地赋值和交换了
            L.ar[0] = L.ar[i];  //哨兵
            int j;
            for (j = i-interval; j>0 && L.ar[0]<L.ar[j]; j-=interval)
                L.ar[j+interval] = L.ar[j]; //后移数据
            L.ar[j+interval] = L.ar[0]; //接着插空，其实如果for没循环一次，j=i-interval, j+interval=i,原地交换
        }
    }
}
void ShellSort(SqList &L, int interval_list[], int n) {
    for (int i = 0; i < n; i++)
        ShellInsert(L, interval_list[i]);
}

//快速排序
void QuickSort(SqList &L, int low, int high) {
    //退出递归条件
    if (low >= high) {  //注意可能有low大于high的情况
        //当前区间就一个元素，直接返回
        return;
    }
    //记录下当前排序的区段
    int begin = low;
    int end = high;
    //选取第一个元素作为pivot(枢轴)
    L.ar[0] = L.ar[low];    //此时low已为空，从low开始插入
    bool flag = true;       //记录在low插入还是在high插入，true在low插入，从high开始遍历
    while (low != high) {   //low high向中间靠拢，直到相等时靠到最中间
        if (flag) { //!从high开始遍历，在low插入
            if (L.ar[high] < L.ar[0]) { //小于哨兵，插入low
                L.ar[low] = L.ar[high];
                flag = false;   //元素被移走了，high保持，不要移动，等着被插入
            } else {
                high--; //没有被移走才要让指针移动
            }
        } else {    //!从high开始遍历，在high插入，
            if (L.ar[low] > L.ar[0]) {  //大于哨兵，插入high
                L.ar[high] = L.ar[low];
                flag = true;
            } else {
                low++;
            }
        }
    }
    //middle == low == high
    L.ar[low] = L.ar[0];    //把哨兵填回中间
    //递归排序子序列
    QuickSort(L, begin, low-1);
    QuickSort(L, low+1, end);
}

//堆排序
void HeapAdjust(SqList &L, int begin, int end) {
    //begin是根节点，要对将begin与子树交换使它符合大顶堆定义
    //这个函数是处理只有根不一定对的堆
    while (true) {
        int left = 2*begin;     //左孩子(若有)
        int right = 2*begin+1;  //右孩子(若有)
        int max_i = begin;  //记录根，左右孩子最大的节点

        if (left<=end && L.ar[max_i]<L.ar[left])
            max_i = left;
        if (right<=end && L.ar[max_i]<L.ar[right])
            max_i = right;
        
        if (max_i == begin)
            break;; //根节点已是最大值，不用adjust了
        //swap
        int temp = L.ar[begin];
        L.ar[begin] = L.ar[max_i];
        L.ar[max_i] = temp;

        begin = max_i;  //更新begin继续向下adjust，不必递归
    }
}
void HeapSort(SqList &L) {
    //构建大顶堆
    for (int i = L.length/2; i >= 1; i--)    //i=1时是adjust 1~length整个数组
        //最后一个节点=2*i或2*i+1，它的父节点是i，所以从length/2开始遍历
        //i是所有非叶子节点从后往前遍历，逐步扩大数组或者说树的范围，逐步构建大顶堆
        HeapAdjust(L, i, L.length);

    //根据大顶堆排序
    for (int i = L.length; i > 1; i--) {    //>1才遍历，i=1时，只有一个元素
        //将大顶堆的根(最大值)移到后面
        int temp = L.ar[1];
        L.ar[1] = L.ar[i];
        L.ar[i] = temp;
        HeapAdjust(L, 1, i-1);  //将剩下前面未排序的更新为大顶堆
    }
}

//归并排序
void merge(int ar1[], int ar2[], int begin, int middle, int end) {
    //普通的合并两个有序数组
    int i = begin;      //有序数组1,ar[begin~middle]
    int j = middle+1;   //有序数组2,ar[middle+1~end]
    int k = begin;      //合并后的数组
    while (i<=middle && j <=end) {
        if (ar1[i] <= ar1[j])
            ar2[k++] = ar1[i++];
        else
            ar2[k++] = ar1[j++];
    }
    while (i<=middle)
        ar2[k++] = ar1[i++];
    while (j<=end)
        ar2[k++] = ar1[j++];
}
void MSort(int ar[], int ar2[], int begin, int end) {
    //将ar1拆分然后合并到ar2，ar的值的索引为1~length
    if (begin == end) { //拆分到最小，仅一个元素，直接将源复制给目标
        ar2[begin] = ar[begin];
        return;
    }
    int middle = (begin+end) / 2;
    int temp[MAXSIZE];
    //将ar的begin至end区段分成两份，存入temp数组中
    MSort(ar, temp, begin, middle);
    MSort(ar, temp, middle+1, end);
    //合并temp数组(内部两段已经排好序)至ar2目标中
    merge(temp, ar2, begin, middle, end);
}
void MergeSort(SqList &L) {
    //将ar归并排序后放入ar，因为内部使用了temp暂存拆分的两个子数组，所以可以让源和目标数组相同
    MSort(L.ar, L.ar, 1, L.length);
}

int main() {
    int n;
    ifstream input ("input.txt", ios::in);
    SqList L;

    while (input >> n)
    {
        L.length = n;
        for (int i = 1; i <= n; i++)
            input >> L.ar[i];
        cout << "原数组："; show(L);

        //shell sort
        SqList L1 = L;
        cout << "希尔排序：";
        int interval_list[2] = {5, 1};
        ShellSort(L1, interval_list, 2);
        show(L1);

        //quick sort
        SqList L2 = L;
        cout << "快速排序：";
        QuickSort(L2, 1, L2.length);
        show(L2);

        //heap sort
        SqList L3 = L;
        cout << "堆 排 序：";
        HeapSort(L3);
        show(L3);

        //merge sort
        SqList L4 = L;
        cout << "归并排序：";
        MergeSort(L4);
        show(L4);

        cout << endl << endl;
    }

    input.close();

    return 0;
}