/*
描述
输入两个递增的链表，单个链表的长度为n，合并这两个链表并使新链表中的节点仍然是递增排序的。
数据范围： 0≤n≤1000，−1000≤节点值≤1000
要求：空间复杂度 O(1)，时间复杂度 O(n)

如输入{1,3,5},{2,4,6}时，合并后的链表为{1,2,3,4,5,6}，所以对应的输出为{1,2,3,4,5,6}，转换过程如下图所示：


或输入{-1,2,4},{1,3,4}时，合并后的链表为{-1,1,2,3,4,4}，所以对应的输出为{-1,1,2,3,4,4}，转换过程如下图所示：

示例1
输入：
{1,3,5},{2,4,6}
返回值：
{1,2,3,4,5,6}

示例2
输入：
{},{}
返回值：
{}

示例3
输入：
{-1,2,4},{1,3,4}
返回值：
{-1,1,2,3,4,4}
*/

typedef struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
} ListNode;

class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param pHead1 ListNode类 
     * @param pHead2 ListNode类 
     * @return ListNode类
     */
    ListNode* Merge(ListNode* pHead1, ListNode* pHead2) {
        if (pHead1==nullptr){
            return pHead2;
        } else if (pHead2==nullptr){
            return pHead1;
        }
        //选择头结点最小的一个作为主链开始
        ListNode *head, *q, *p, *last;
        if (pHead1->val > pHead2->val){
            head = pHead2;
            q = pHead1;
        }  else{
            head = pHead1;
            q = pHead2;
        }
        p = head->next;
        last = head; //记录合并链表的末尾位置

        while (p){
            if (q==nullptr){  //主链更长
                last->next = p;
                return head;  //已经合并完，直接return
            }
            if (p->val <= q->val){ //该插入的值在主链上，主链步进
                last->next = p;
                last = p;
                p = p->next;
            } else{ //该插入的值在支链，支链步进
                last->next = q;
                last = q;
                q = q->next;
            }
        }
        //while 结束，主链已经遍历完，此时支链必不是nullptr
        last->next = q;
        return head;
    }
};