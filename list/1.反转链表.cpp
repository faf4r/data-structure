/*
描述
给定一个单链表的头结点pHead(该头节点是有值的，比如在下图，它的val是1)，长度为n，反转该链表后，返回新链表的表头。

数据范围： 0≤n≤1000
要求：空间复杂度 O(1) ，时间复杂度 O(n) 。

如当输入链表{1,2,3}时，
经反转后，原链表变为{3,2,1}，所以对应的输出为{3,2,1}。

示例1
输入：
{1,2,3}
返回值：
{3,2,1}

示例2
输入：
{}
返回值：
{}
说明：
空链表则输出空    
*/

#include <iostream>

typedef struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
} ListNode;


class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     * 注意题目要求head是存元素值的
     * 
     * @param head ListNode类 
     * @return ListNode类
     */
    ListNode* ReverseList(ListNode* head) {
        if (head==NULL || head->next==NULL) return head;  //处理空链表和next为空的情况情况
        ListNode *prev=NULL, *current=head, *follow=head->next;
        while (follow){
            current->next = prev;
            prev = current;
            current = follow;
            follow = follow->next;
        }
        current->next = prev;  //上面循环完current是最后一个值，但是还没指向prev
        return current;
    }
};