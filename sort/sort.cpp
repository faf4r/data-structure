#include <iostream>
#include <fstream>

using namespace std;

#define MAXSIZE 100

typedef struct {
    int ar[MAXSIZE+1];  //ar[0]���ڱ�
    int length;
} SqList;

void show(SqList L) {
    for (int i = 1; i <= L.length; i++)
        cout << L.ar[i] << " ";
    cout << endl;
}

//ϣ������
void ShellInsert(SqList &L, int interval) {
    for (int i = interval+1; i <= L.length; i++) {
        if (L.ar[i] < L.ar[i-interval]) {   //���������ż�������Ȼ����ԭ�ظ�ֵ�ͽ�����
            L.ar[0] = L.ar[i];  //�ڱ�
            int j;
            for (j = i-interval; j>0 && L.ar[0]<L.ar[j]; j-=interval)
                L.ar[j+interval] = L.ar[j]; //��������
            L.ar[j+interval] = L.ar[0]; //���Ų�գ���ʵ���forûѭ��һ�Σ�j=i-interval, j+interval=i,ԭ�ؽ���
        }
    }
}
void ShellSort(SqList &L, int interval_list[], int n) {
    for (int i = 0; i < n; i++)
        ShellInsert(L, interval_list[i]);
}

//��������
void QuickSort(SqList &L, int low, int high) {
    //�˳��ݹ�����
    if (low >= high) {  //ע�������low����high�����
        //��ǰ�����һ��Ԫ�أ�ֱ�ӷ���
        return;
    }
    //��¼�µ�ǰ���������
    int begin = low;
    int end = high;
    //ѡȡ��һ��Ԫ����Ϊpivot(����)
    L.ar[0] = L.ar[low];    //��ʱlow��Ϊ�գ���low��ʼ����
    bool flag = true;       //��¼��low���뻹����high���룬true��low���룬��high��ʼ����
    while (low != high) {   //low high���м俿£��ֱ�����ʱ�������м�
        if (flag) { //!��high��ʼ��������low����
            if (L.ar[high] < L.ar[0]) { //С���ڱ�������low
                L.ar[low] = L.ar[high];
                flag = false;   //Ԫ�ر������ˣ�high���֣���Ҫ�ƶ������ű�����
            } else {
                high--; //û�б����߲�Ҫ��ָ���ƶ�
            }
        } else {    //!��high��ʼ��������high���룬
            if (L.ar[low] > L.ar[0]) {  //�����ڱ�������high
                L.ar[high] = L.ar[low];
                flag = true;
            } else {
                low++;
            }
        }
    }
    //middle == low == high
    L.ar[low] = L.ar[0];    //���ڱ�����м�
    //�ݹ�����������
    QuickSort(L, begin, low-1);
    QuickSort(L, low+1, end);
}

//������
void HeapAdjust(SqList &L, int begin, int end) {
    //begin�Ǹ��ڵ㣬Ҫ�Խ�begin����������ʹ�����ϴ󶥶Ѷ���
    //��������Ǵ���ֻ�и���һ���ԵĶ�
    while (true) {
        int left = 2*begin;     //����(����)
        int right = 2*begin+1;  //�Һ���(����)
        int max_i = begin;  //��¼�������Һ������Ľڵ�

        if (left<=end && L.ar[max_i]<L.ar[left])
            max_i = left;
        if (right<=end && L.ar[max_i]<L.ar[right])
            max_i = right;
        
        if (max_i == begin)
            break;; //���ڵ��������ֵ������adjust��
        //swap
        int temp = L.ar[begin];
        L.ar[begin] = L.ar[max_i];
        L.ar[max_i] = temp;

        begin = max_i;  //����begin��������adjust�����صݹ�
    }
}
void HeapSort(SqList &L) {
    //�����󶥶�
    for (int i = L.length/2; i >= 1; i--)    //i=1ʱ��adjust 1~length��������
        //���һ���ڵ�=2*i��2*i+1�����ĸ��ڵ���i�����Դ�length/2��ʼ����
        //i�����з�Ҷ�ӽڵ�Ӻ���ǰ�������������������˵���ķ�Χ���𲽹����󶥶�
        HeapAdjust(L, i, L.length);

    //���ݴ󶥶�����
    for (int i = L.length; i > 1; i--) {    //>1�ű�����i=1ʱ��ֻ��һ��Ԫ��
        //���󶥶ѵĸ�(���ֵ)�Ƶ�����
        int temp = L.ar[1];
        L.ar[1] = L.ar[i];
        L.ar[i] = temp;
        HeapAdjust(L, 1, i-1);  //��ʣ��ǰ��δ����ĸ���Ϊ�󶥶�
    }
}

//�鲢����
void merge(int ar1[], int ar2[], int begin, int middle, int end) {
    //��ͨ�ĺϲ�������������
    int i = begin;      //��������1,ar[begin~middle]
    int j = middle+1;   //��������2,ar[middle+1~end]
    int k = begin;      //�ϲ��������
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
    //��ar1���Ȼ��ϲ���ar2��ar��ֵ������Ϊ1~length
    if (begin == end) { //��ֵ���С����һ��Ԫ�أ�ֱ�ӽ�Դ���Ƹ�Ŀ��
        ar2[begin] = ar[begin];
        return;
    }
    int middle = (begin+end) / 2;
    int temp[MAXSIZE];
    //��ar��begin��end���ηֳ����ݣ�����temp������
    MSort(ar, temp, begin, middle);
    MSort(ar, temp, middle+1, end);
    //�ϲ�temp����(�ڲ������Ѿ��ź���)��ar2Ŀ����
    merge(temp, ar2, begin, middle, end);
}
void MergeSort(SqList &L) {
    //��ar�鲢��������ar����Ϊ�ڲ�ʹ����temp�ݴ��ֵ����������飬���Կ�����Դ��Ŀ��������ͬ
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
        cout << "ԭ���飺"; show(L);

        //shell sort
        SqList L1 = L;
        cout << "ϣ������";
        int interval_list[2] = {5, 1};
        ShellSort(L1, interval_list, 2);
        show(L1);

        //quick sort
        SqList L2 = L;
        cout << "��������";
        QuickSort(L2, 1, L2.length);
        show(L2);

        //heap sort
        SqList L3 = L;
        cout << "�� �� ��";
        HeapSort(L3);
        show(L3);

        //merge sort
        SqList L4 = L;
        cout << "�鲢����";
        MergeSort(L4);
        show(L4);

        cout << endl << endl;
    }

    input.close();

    return 0;
}