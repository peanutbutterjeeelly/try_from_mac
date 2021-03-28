#include<iostream>
#include<vector>
#include<stack>
#include<string>
#include<memory>
#include<algorithm>
#include<functional>
#include<queue>
#include <stdio.h>
#include<string>
#include<sstream>
#include<istream>
#include <thread>
#include <mutex>
#include <map>
#include <unordered_map>
#include<unordered_set>
#include <assert.h>

using namespace std;

//commit something
//test







































struct DLinkedNode {
	int key, value;
	DLinkedNode* prev;
	DLinkedNode* next;

	DLinkedNode()
			:key(0), value(0), prev(nullptr), next(nullptr) { }

	DLinkedNode(int _key, int _value)
			:key(_key), value(_value), prev(nullptr), next(nullptr) { }
};

class LRUCache {
private:
	unordered_map<int, DLinkedNode*> cache;
	DLinkedNode* head;
	DLinkedNode* tail;
	int size;
	int capacity;
public:
	LRUCache(int _capacity)
			:capacity(_capacity), size(0)
	{
		head = new DLinkedNode();
		tail = new DLinkedNode();
		head->next = tail;
		tail->prev = head;
	}

	void addToHead(DLinkedNode* node)
	{
		node->prev = head;
		node->next = head->next;
		head->next->prev = node;
		head->next = node;
	}

	void removeNode(DLinkedNode* node)
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}

	void moveToHead(DLinkedNode* node)
	{
		removeNode(node);
		addToHead(node);
	}

	DLinkedNode* removeTail()
	{
		DLinkedNode* node = tail->prev;
		removeNode(node);
		return node;
	}

	int get(int key)
	{
		if (!cache.count(key)) {
			return -1;
		}
		DLinkedNode* node = cache[key];
		moveToHead(node);
		return node->value;
	}

	void put(int key, int value)
	{
		if (!cache.count(key)) {
			DLinkedNode* node = new DLinkedNode(key, value);
			cache[key] = node;
			addToHead(node);
			++size;
			if (size>capacity) {
				DLinkedNode* removed = removeTail();
				cache.erase(removed->key);
				delete removed;
				--size;
			}
		}
		else {
			DLinkedNode* node = cache[key];
			node->value = value;
			moveToHead(node);
		}
	}
};

class course {
public:
	string name;
	int section;
	int credits;

	course() { }

	course(string n, int s, int c)
			:name(n), section(s), credits(c) { }

};

class Node          //组成双向链表的节点
{
public:
	int data;
	Node* pNext;
	Node* pLast;
};

class List      //构造一个双向链表
{
private:
	Node* pHead;
	Node* pTail;
	int length;
public:
	List(int length)
	{
		this->length = length;
		pHead = new Node();
		pHead->pLast = NULL;
		pTail = pHead;
		for (int i = 0; i<length; i++) {
			Node* temp = new Node();
			cout << "please enter the no" << i+1 << " Node's data:";
			cin >> temp->data;
			temp->pNext = NULL;
			temp->pLast = pTail;
			pTail->pNext = temp;
			pTail = temp;
		}
	}

	void traverseList()
	{
		Node* p = pHead->pNext;
		while (p!=NULL) {
			cout << p->data << endl;
			p = p->pNext;
		}
	}

	void traverseListReturn()
	{
		Node* p = pTail;
		while (p->pLast!=NULL) {
			cout << p->data << endl;
			p = p->pLast;
		}
	}

	void sortList()
	{
		Node* p = new Node();
		Node* q = new Node();
		int temp;
		for (p = pHead->pNext; p->pNext!=NULL; p = p->pNext) {
			for (q = p->pNext; q!=NULL; q = q->pNext) {
				if (q->data<p->data) {
					temp = q->data;
					q->data = p->data;
					p->data = temp;
				}
			}
		}
	}

	void sortListByInsertWay()
	{
		if (pHead->pNext==NULL || pHead->pNext->pNext==NULL) {
			return;
		}
		Node* p2 = pHead->pNext->pNext;
		Node* p1 = pHead;
		pHead->pNext->pNext = NULL;
		while (p2) {
			Node* pN = p2->pNext;
			while (p1->pNext) {
				if (p2->data<p1->pNext->data) {
					p2->pNext = p1->pNext;
					p2->pLast = p1;
					p1->pNext->pLast = p2;
					p1->pNext = p2;
					break;
				}
				p1 = p1->pNext;
			}
			if (p1->pNext==NULL) {
				p2->pNext = NULL;
				p2->pLast = p1;
				p1->pNext = p2;
			}
			p2 = pN;
		}

		//重新查找pTail的位置
		Node* pt = pHead;
		while (pt->pNext) {
			pt = pt->pNext;
		}
		pTail = pt;
	}

	void changeList(int num, int position)
	{
		Node* p = pHead->pNext;
		if (position>length || position<=0) {
			cout << "over stack !" << endl;
			return;
		}
		for (int i = 0; i<position-1; i++) {
			p = p->pNext;
		}
		p->data = num;
	}

	void insertList(int num, int position)
	{
		Node* p = pHead->pNext;
		if (position>length || position<=0) {
			cout << "over stack !" << endl;
			return;
		}
		for (int i = 0; i<position-1; i++) {
			p = p->pNext;
		}
		Node* temp = new Node();
		temp->data = num;
		temp->pNext = p;
		temp->pLast = p->pLast;
		p->pLast->pNext = temp;
		p->pLast = temp;
		length++;
	}

	void clearList()
	{
		Node* q;
		Node* p = pHead->pNext;
		while (p!=NULL) {
			q = p;
			p = p->pNext;
			delete q;
		}
		p = NULL;
		q = NULL;
	}

	void deleteList(int position)
	{
		Node* p = pHead->pNext;
		if (position>length || position<=0) {
			cout << "over stack !" << endl;
			return;
		}
		for (int i = 0; i<position-1; i++) {
			p = p->pNext;
		}
		p->pLast->pNext = p->pNext;
		p->pNext->pLast = p->pLast;
		delete p;
		length--;
	}

	int getItemInList(int position)
	{
		Node* p = pHead->pNext;
		if (position>length || position<=0) {
			cout << "over stack !" << endl;
			return 0;
		}
		for (int i = 0; i<position-1; i++) {
			p = p->pNext;
		}
		return p->data;
	}

	~List()
	{
		Node* q;
		Node* p = pHead->pNext;
		while (p!=NULL) {
			q = p;
			p = p->pNext;
			delete q;
		}
		p = NULL;
		q = NULL;
	}

};

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;

	TreeNode(int x)
			:val(x), left(nullptr), right(nullptr) { }

	TreeNode()
			:left(nullptr), right(nullptr) { }
};

struct ListNode {
	int val;
	ListNode* next;

	ListNode(int x)
			:val(x), next(nullptr) { }

	ListNode()
			:next(nullptr) { }
};

class SinglyLinkedList {
public:
	ListNode* head;

	SinglyLinkedList()
			:head(nullptr) { }

	SinglyLinkedList(const initializer_list<int>& I);

};

SinglyLinkedList::SinglyLinkedList(const initializer_list<int>& I)
{
	head = nullptr;
	auto p1{ I.end()-1 };
	while (p1!=I.begin()-1) {
		ListNode* p2 = new ListNode(*p1);
		p2->next = head;
		head = p2;
		p1 = p1-1;
	}
}

//Binary tree
class getMinDepth {
public:
	int getDepth(TreeNode* node)
	{
		if (node==nullptr) return 0;
		int leftDepth = getDepth(node->left);
		int rightDepth = getDepth(node->right);
		if (node->left==nullptr && node->right!=nullptr) {
			return 1+rightDepth;
		}
		if (node->left!=nullptr && node->right==nullptr) {
			return 1+leftDepth;
		}
		int result = 1+min(leftDepth, rightDepth);
		return result;
	}

	int minDepth_dfs(TreeNode* root)
	{
		return getDepth(root);
	}

	int minDepth_bfs(TreeNode* root)
	{
		if (root==nullptr) {
			return 0;
		}
		int depth = 0;
		queue<TreeNode*> que;
		que.push(root);
		while (!que.empty()) {
			int size = que.size();
			depth++;
			int flag = 0;
			for (int i = 0; i<size; i++) {
				TreeNode* node = que.front();
				que.pop();
				if (node->left)que.push(node->left);
				if (node->right)que.push(node->right);
				if (!node->left && !node->right) {
					flag = 1;
					break;
				}
			}
			if (flag==1) break;
		}
		return depth;
	}
};

class preorder {
public:
	vector<int> preorder_iterative(TreeNode* root)
	{
		stack<TreeNode*> st;
		vector<int> result;
		st.push(root);
		while (!st.empty()) {
			TreeNode* tmp = st.top();
			st.pop();
			result.push_back(tmp->val);
			if (tmp->right!=nullptr) st.push(tmp->right);
			if (tmp->left!=nullptr)st.push(tmp->left);
		}
		return result;
	}

	void traversal(TreeNode* cur, vector<int>& vec)
	{
		if (cur==nullptr) return;
		vec.push_back(cur->val);
		traversal(cur->left, vec);
		traversal(cur->right, vec);
	}

	vector<int> preorderTraversal(TreeNode* root)
	{
		vector<int> result;
		traversal(root, result);
		return result;
	}
};

class inorder {
public:
	vector<int> inorder_iterative(TreeNode* root)
	{
		stack<TreeNode*> st;
		vector<int> res;
		TreeNode* cur = root;
		while (cur!=nullptr || !st.empty()) {
			if (cur!=nullptr) {
				st.push(cur);
				cur = cur->left;
			}
			else {
				cur = st.top();
				st.pop();
				res.push_back(cur->val);
				cur = cur->right;
			}
		}
		return res;
	}
};

class postorder {
public:
	vector<int> postorder_iterative(TreeNode* root)
	{
		stack<TreeNode*> st;
		vector<int> result;
		st.push(root);
		while (!st.empty()) {
			TreeNode* tmp = st.top();
			st.pop();
			result.push_back(tmp->val);
			if (tmp->left!=nullptr)st.push(tmp->left);
			if (tmp->right!=nullptr) st.push(tmp->right);
		}
		reverse(result.begin(), result.end());
		return result;
	}
};

class levelorder {
public:
	vector<vector<int>> LevelOrder(TreeNode* root)
	{
		queue<TreeNode*> que;
		if (root!=nullptr) que.push(root);
		vector<vector<int>> res;
		while (!que.empty()) {
			int size = que.size();
			vector<int> vec;
			for (int i = 0; i<size; i++) {
				TreeNode* tmp = que.front();
				que.pop();
				vec.push_back(tmp->val);
				if (tmp->left!=nullptr) que.push(tmp->left);
				if (tmp->right!=nullptr) que.push(tmp->right);
			}
			res.push_back(vec);
		}
		return res;
	}
};

class zlevelorder {
public:
	vector<vector<int>> zlevel(TreeNode* root)
	{
		vector<vector<int>> res;
		if (root==nullptr) return res;
		bool flag = true;
		deque<TreeNode*> q;
		q.push_back(root);
		while (!q.empty()) {
			int n = q.size();
			vector<int> out;
			TreeNode* node;
			while (n>0) {
				if (flag) {
					node = q.front();
					q.pop_front();
					if (node->left) {
						q.push_back(node->left);
					}
					if (node->right) {
						q.push_back(node->right);
					}
				}
				else {
					node = q.back();
					q.pop_back();
					if (node->right) {
						q.push_back(node->right);
					}
					if (node->left) {
						q.push_back(node->left);
					}
				}
				out.push_back(node->val);
				n--;
			}
			flag = !flag;
			res.push_back(out);

		}
		return res;
	}
};

class sametree {
public:
	bool isSameTree(TreeNode* p, TreeNode* q)
	{
		if (p==nullptr && q==nullptr) {
			return true;
		}
		else if (p==nullptr || q==nullptr) {
			return false;
		}
		else if (p->val!=q->val) {
			return false;
		}
		else {
			return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
		}
	}
};

class InvertTree {
public:
	TreeNode* invertTree(TreeNode* root)
	{
		queue<TreeNode*> que;
		if (root!=nullptr) que.push(root);
		while (!que.empty()) {
			int size = que.size();
			for (int i = 0; i<size; i++) {
				TreeNode* node = que.front();
				que.pop();
				swap(node->left, node->right);
				if (node->left)que.push(node->left);
				if (node->right)que.push(node->right);
			}
		}
		return root;
	}
};

class RightSide {
public:
	vector<int> rightSideView(TreeNode* root)
	{
		queue<TreeNode*> que;
		if (root!=nullptr) que.push(root);
		vector<int> result;
		while (!que.empty()) {
			int size = que.size();
			for (int i = 0; i<size; i++) {
				TreeNode* node = que.front();
				que.pop();
				if (i==(size-1))result.push_back(node->val);
				if (node->left)que.push(node->left);
				if (node->right)que.push(node->right);

			}
		}
		return result;
	}

};

class GetDepth {
public:
	int getdepth(TreeNode* node)
	{
		if (node==nullptr) {
			return 0;
		}
		int leftdepth = getdepth(node->left);
		int rightdepth = getdepth(node->right);
		int depth = 1+max(leftdepth, rightdepth);
		return depth;
	}

	int maxdepth(TreeNode* root)
	{
		return getdepth(root);
	}
};

class isBinaryTreeBalanced {
public:
	int getdepth(TreeNode* node)
	{
		if (node==nullptr) {
			return 0;
		}
		int leftDepth = getdepth(node->left);
		if (leftDepth==-1)return -1;
		int rightDepth = getdepth(node->right);
		if (rightDepth==-1)return -1;
		return abs(leftDepth-rightDepth)>1 ? -1 : 1+max(leftDepth, rightDepth);
	}

	bool isbalanced(TreeNode* root)
	{
		return getdepth(root)==-1 ? false : true;
	}
};

//strings, ints and overflows
int gcd(int x, int y)
{
	int z = y;
	while (x%y!=0) {
		z = x%y;
		x = y;
		y = z;
	}
	return z;
}

int intOverFlow(unsigned int i, unsigned int j)
{//判断两个无符号整形相加产生溢出
	int sum = 0;
	sum = (int)(i+j-pow(2, 32));
	if (sum<i && sum<j) {

		return 1;

	}

	return 0;
}

class AddtwoNumber {
public:
	int add(int a, int b)
	{

		int n, m;
		while (b!=0) {
			//这是无进位的情况。
			n = a ^ b;
			//进位的。
			m = (unsigned int)(a & b) << 1; // 转换成无符号数。可能有负数的情况。
			a = n;
			b = m;  // 一直到进位的情况为 0，退出循环。
		}
		return a;
	}
};

class split {
public:
	int strToInt(string str)
	{
		int i = 0, flag = 1;
		long res = 0;
		while (str[i]==' ') i++;
		if (str[i]=='-') flag = -1;
		if (str[i]=='-' || str[i]=='+') i++;
		for (; i<str.size() && isdigit(str[i]); i++) {
			res = res*10+(str[i]-'0');
			if (res>=INT_MAX && flag==1) return INT_MAX;
			if (res>INT_MAX && flag==-1)return INT_MIN;
		}
		return flag*res;
	}

	vector<int> Split(string str, char pattern)
	{
		vector<int> res;
		string temp;
		string num;
		for (auto i : str) {
			if (isdigit(i) || i==pattern || i=='+' || i=='-') {//clean string to make sure no special char
				temp.push_back(i);
			}
		}
		temp += pattern;
		cout << temp;
		for (auto i : temp) {
			if (i!=pattern) {
				num.push_back(i);
			}
			else if (i==pattern && num!="") {
				res.push_back(strToInt(num));
				num.clear();
			}
			//else if (i == pattern && num == "") {
			//	continue;
			//}

		}
		return res;
	}
};

class offer67 {//str to int
public:
	int strToInt(string str)
	{
		int i = 0, flag = 1;
		long res = 0;
		while (str[i]==' ') i++;
		if (str[i]=='-') flag = -1;
		if (str[i]=='-' || str[i]=='+') i++;
		for (; i<str.size() && isdigit(str[i]); i++) {
			res = res*10+(str[i]-'0');
			if (res>=INT_MAX && flag==1) return INT_MAX;
			if (res>INT_MAX && flag==-1)return INT_MIN;
		}
		return flag*res;
	}
};

//array
class MergeSortedArray {
public:
	//输入：nums1 = [1, 2, 3, 0, 0, 0], m = 3, nums2 = [2, 5, 6], n = 3
	//输出：[1, 2, 2, 3, 5, 6]
	void merge(vector<int>& nums1, int m, vector<int>& nums2, int n)
	{
		if (!m) {
			for (int i = 0; i<n; ++i) {
				nums1[i] = nums2[i];
			}
		}
		int p1 = m-1, p2 = n-1, i;
		for (i = m+n-1; i>=0 && p1>=0 && p2>=0; --i) {
			nums1[i] = (nums2[p2]>nums1[p1]) ? nums2[p2--] : nums1[p1--];
		}
		if (p1<0) {
			for (int j = 0; j<=1; ++j) {
				nums1[j] = nums2[j];
			}
		}

	}

};

class offer03 {//剑指 Offer 03. 数组中重复的数字
public:
	int findRepeatNumber(vector<int>& nums)
	{
		for (int i = 0; i<nums.size(); i++) {
			while (nums[i]!=i) {
				if (nums[i]==nums[nums[i]]) {
					return nums[i];
				}
				swap(nums[i], nums[nums[i]]);
			}
		}
		return -1;
	}
};

class Leetcode384 {//shuffle the cards
private:
	vector<int> data;
public:
	Leetcode384(vector<int>& nums)
	{
		data = nums;
	}

	vector<int> reset()
	{
		return data;
	}

	vector<int> shuffle()
	{
		vector<int> res(data);
		for (int i = 0; i<res.size(); i++) {
			swap(res[i], res[rand()%(i+1)]);
		}
		return res;
	}
};

class fib {
public:
	int climbStairs(int n)
	{//dp, saves time complexity
		vector<int> dp(n+3);
		dp[1] = 1;
		dp[2] = 2;
		for (int i = 3; i<=n; i++)
			dp[i] = dp[i-1]+dp[i-2];
		return dp[n];
	}

};

class Leetcode35 {//binary search
public:
	int searchInsert(vector<int>& nums, int target)
	{
		int n = nums.size();
		int left = 0;
		int right = n-1;
		while (left<=right) {
			int middle = left+((right-left)/2);
			if (nums[middle]>target) {// target 在左区间，所以[left, middle - 1]
				right = middle-1;
			}
			else if (nums[middle]<target) {
				left = middle+1;// target 在右区间，所以[middle + 1, right]
			}
			else {
				return middle;
			}
		}
		// 分别处理如下四种情况
		// 目标值在数组所有元素之前  [0, -1]
		// 目标值等于数组中某一个元素  return middle;
		// 目标值插入数组中的位置 [left, right]，return  right + 1
		// 目标值在数组所有元素之后的情况 [left, right]， return right + 1
		return right+1;
	}
};

class Leetcode26 {
public:
	int removeDuplicates(vector<int> nums)
	{//remove duplicate element
		int length = nums.size();
		if (length==0) {
			return 0;
		}
		int slow = 0, fast = 0;
		while (fast<length) {
			if (nums[fast]!=nums[slow]) {
				slow++;
				// 维护 nums[0..slow] 无重复
				nums[slow] = nums[fast];
			}
			fast++;
		}
		// 数组长度为索引 + 1
		return slow+1;
	}

};

class Leetcode27 {//remove element, given value
public:
	int removeElement(vector<int>& nums, int val)
	{//bruteforce
		int size = nums.size();
		for (int i = 0; i<size; i++) {
			if (nums[i]==val) { // 发现需要移除的元素，就将数组集体向前移动一位
				for (int j = i+1; j<size; j++) {
					nums[j-1] = nums[j];
				}
				//cout << nums[i] << endl;
				i--;// 因为下表i以后的数值都向前移动了一位，所以i也向前移动一位
				//cout << nums[i] << endl;
				size--;// 此时数组的大小-1

			}
		}
		return size;
	}

	int removeElementDoubleP(vector<int>& nums, int val)
	{
		//双指针法
		int slowIndex = 0;
		for (int fastIndex = 0; fastIndex<nums.size(); fastIndex++) {
			if (val!=nums[fastIndex]) {
				nums[slowIndex++] = nums[fastIndex];
			}
		}
		return slowIndex;
	}
};

class Leetcode209 {
public:
	int minSubArrayLen(int s, vector<int>& nums)
	{
		int result = INT32_MAX;
		int sum = 0;
		int subLength = 0;
		for (int i = 0; i<nums.size(); i++) {
			sum = 0;
			for (int j = i; j<nums.size(); j++) {
				if (sum>=s) {
					subLength = j-i+1;
					result = result<subLength ? result : subLength;
					break;
				}
			}

		}
		return result==INT32_MAX ? 0 : result;
	}

	int minSubArrayLenSlidingWindow(int s, vector<int>& nums)
	{
		int result = INT32_MAX;
		int sum = 0;
		int subLength = 0;
		int i = 0;
		for (int j = 0; j<nums.size(); j++) {
			sum += nums[j];
			while (sum>=s) {
				subLength = (j-i+1);
				result = result<subLength ? result : subLength;
				sum -= nums[i++];
			}
		}
		return result==INT32_MAX ? 0 : result;
	}
};

class Leetcode59 {//SpiralMatrix
public:
	vector<vector<int>> SpiralMatrix(int n)
	{
		vector<vector<int>> res(n, vector<int>(n, 0));
		int startx = 0, starty = 0; // 定义每循环一个圈的起始位置
		int loop = n/2; // 每个圈循环几次，例如n为奇数3，那么loop = 1 只是循环一圈，矩阵中间的值需要单独处理
		int mid = n/2; // 矩阵中间的位置，例如：n为3， 中间的位置就是(1，1)，n为5，中间位置为(2, 2)
		int count = 1; // 用来给矩阵中每一个空格赋值
		int offset = 1; // 每一圈循环，需要控制每一条边遍历的长度
		int i, j;
		while (loop--) {
			i = startx;
			j = starty;

			// 下面开始的四个for就是模拟转了一圈
			// 模拟填充上行从左到右(左闭右开)
			for (j = starty; j<starty+n-offset; j++) {
				res[startx][j] = count++;
			}
			// 模拟填充右列从上到下(左闭右开)
			for (i = startx; i<startx+n-offset; i++) {
				res[i][j] = count++;
			}
			// 模拟填充下行从右到左(左闭右开)
			for (; j>starty; j--) {
				res[i][j] = count++;
			}
			// 模拟填充左列从下到上(左闭右开)
			for (; i>startx; i--) {
				res[i][j] = count++;
			}

			// 第二圈开始的时候，起始位置要各自加1， 例如：第一圈起始位置是(0, 0)，第二圈起始位置是(1, 1)
			startx++;
			starty++;

			// offset 控制每一圈里每一条边遍历的长度
			offset += 2;
		}

		// 如果n为奇数的话，需要单独给矩阵最中间的位置赋值
		if (n%2) {
			res[mid][mid] = count;
		}
		return res;
	}
};

class Leetcode344 {//reverseString
public:
	void reverseString(vector<char>& s)
	{
		for (int i = 0, j = s.size()-1; i<s.size()/2; i++, j--) {
			swap(s[i], s[j]);
		}
	}
};

//linkedlist..
class Node_class {
public:
	int val;
	Node_class* next;
	Node_class* random;

	explicit Node_class(int _val)
	{
		val = _val;
		next = nullptr;
		random = nullptr;
	}
};
class copy_random_List{
private:
	unordered_map<Node_class*, Node_class*> dic;
public:
	Node_class* copyRandomList(Node_class* head){
		if (head == nullptr) return nullptr;
		if (dic.count(head)) return dic[head];
		Node_class* root = new Node_class(head->val);
		dic[head] = root;
		root->next = copyRandomList(head->next);
		root->random = copyRandomList(head->random);
		return root;
	}
};

class merge_K_sorted_LL {
public:
	struct cmp {
		bool operator()(ListNode* a, ListNode* b)
		{
			return a->val<b->val;
		}
	};

	ListNode* mergeK_LinkedList_priorityqueue(vector<ListNode*> lists)
	{
		auto cmp = [&](const ListNode* a, const ListNode* b) { return a->val>b->val; };
		priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> q(cmp);
		for (auto& c:lists) if (c) q.push(c);
		ListNode* root = new ListNode(-1), * p = root;
		while (!q.empty()) {
			auto t = q.top();
			q.pop();
			p->next = t;
			p = p->next;
			if (t->next) q.push(t->next);
		}
		return root->next;
	}

	ListNode* merge(ListNode* p1, ListNode* p2)
	{
		if (!p1) return p2;
		if (!p2) return p1;
		if (p1->val<=p2->val) {
			p1->next = merge(p1->next, p2);
			return p1;
		}
		else {
			p2->next = merge(p1, p2->next);
			return p2;
		}
	}

	ListNode* mergeKLists(vector<ListNode*>& lists)
	{
		if (lists.size()==0) return nullptr;
		ListNode* head = lists[0];
		for (int i = 1; i<lists.size(); ++i) {
			if (lists[i]) head = merge(head, lists[i]);
		}
		return head;
	}
};

class merge_two_sorted_LL {
	//输入：l1 = [1, 2, 4], l2 = [1, 3, 4]
	//输出：[1, 1, 2, 3, 4, 4]
public:
	ListNode* mergeTwoLists(ListNode* L1, ListNode* L2)
	{
		ListNode* preHead = new ListNode(-1);
		ListNode* prev = preHead;
		while (L1!=nullptr && L2!=nullptr) {
			if (L1->val<L2->val) {
				prev->next = L1;
				L1 = L1->next;
			}
			else {
				prev->next = L2;
				L2 = L2->next;
			}
			prev = prev->next;
		}
		prev->next = L1==nullptr ? L2 : L1;
		/*如果有一个链表为空了才跳出循环，所以最多有一个还未被合并完*/
		return preHead->next;
	}

	ListNode* mergeTowLists_recursion(ListNode* L1, ListNode* L2)
	{
		if (L1==nullptr) {
			return L2;
		}
		if (L2==nullptr) {
			return L1;
		}
		if (L1->val<=L2->val) {
			L1->next = mergeTwoLists(L1->next, L2);
			return L1;
		}
		L2->next = mergeTwoLists(L1, L2->next);
		return L2;
	}
};

class Leetcode203 {
public:
	ListNode* removeElements(ListNode* head, int val)
	{
		ListNode* dummyHead = new ListNode(0); // 设置一个虚拟头结点
		dummyHead->next = head; // 将虚拟头结点指向head，这样方面后面做删除操作
		ListNode* cur = dummyHead;

		while (cur->next!=nullptr) {
			if (cur->next->val==val) {
				//cout << cur->next->val;
				ListNode* tmp = cur->next;
				cur->next = cur->next->next;
				delete tmp;
			}
			else {
				cur = cur->next;
			}
		}
		return dummyHead->next;
	}
};

ostream& operator<<(ostream& str, const SinglyLinkedList& L)
{
	str << "<< ";
	ListNode* p = L.head;
	while (p) {
		str << p->val << " ";
		p = p->next;//a common error p++;
	}
	str << ">>";

	return str;
}

class sortLinkedList {
public:
	ListNode* selectSortList(ListNode* head)
	{
		//selection sort
		if (head==nullptr || head->next==nullptr) return head;
		ListNode* pstart = new ListNode(0);
		pstart->next = head;
		ListNode* sortedTail = pstart;
		while (sortedTail->next!=nullptr) {
			ListNode* minNode = sortedTail->next, * p = sortedTail->next->next;
			while (p!=nullptr) {
				if (p->val<minNode->val) {
					minNode = p;
				}
				p = p->next;
			}
			swap(minNode->val, sortedTail->next->val);
			sortedTail = sortedTail->next;
		}
		head = pstart->next;
		delete pstart;
		return head;
	}

	ListNode* partitionList(ListNode* low, ListNode* high)
	{
		int key = low->val;
		ListNode* loc = low;
		for (ListNode* i = low->next; i!=high; i = i->next) {
			if (i->val<key) {
				loc = loc->next;
				swap(i->val, loc->val);
			}
		}
		swap(loc->val, low->val);
		return loc;
	}

	void qsortList(ListNode* head, ListNode* tail)
	{
		if (head!=tail && head->next!=tail) {
			ListNode* mid = partitionList(head, tail);
			qsortList(head, mid);
			qsortList(mid->next, tail);
		}
	}

	ListNode* quickSortList(ListNode* head)
	{
		if (head==nullptr || head->next==nullptr) return head;
		qsortList(head, nullptr);
		return head;
	}

};

class Leetcode206 {//reverse linkedlist
public:
	ListNode* reverseLinkedList(ListNode* head)
	{
		ListNode* cur = head;
		ListNode* pre = nullptr;
		ListNode* tmp;
		while (cur) {
			tmp = cur->next;
			cur->next = pre;
			pre = cur;
			cur = tmp;
		}
		return pre;
	}
};

void printLL(ListNode* head)
{//print linkedlist
	cout << "<";
	while (head) {
		cout << head->val;
		cout << " ";
		head = head->next;
	}
	cout << ">" << endl;
}

class Leetcode142 {
public:
	ListNode* detectCycle(ListNode* head)
	{
		ListNode* fast = head;
		ListNode* slow = head;
		while (fast!=NULL && fast->next!=NULL) {
			slow = slow->next;
			fast = fast->next->next;
			// 快慢指针相遇，此时从head 和 相遇点，同时查找直至相遇
			if (slow==fast) {
				ListNode* index1 = fast;
				ListNode* index2 = head;
				while (index1!=index2) {
					index1 = index1->next;
					index2 = index2->next;
				}
				return index2; // 返回环的入口
			}
		}
		return NULL;
	}
};

class GetIntersection {
public:
	ListNode* getIntersectionNode(ListNode* headA, ListNode* headB)
	{
		if (headA==nullptr || headB==nullptr) {
			return nullptr;
		}
		ListNode* pa = headA;
		ListNode* pb = headB;
		int flag = 0;
		while (pa!=pb) {
			if (pa!=nullptr) pa = pa->next;
			else pa = headB;
			if (pb!=nullptr) pb = pb->next;
			else pb = headA;
		}
		return pa;
	}
};

class Leetcode83 {//给定一个排序链表，删除所有重复的元素，使得每个元素只出现一次。
public:
	ListNode* deleteDuplicates(ListNode* head)
	{
		ListNode* pi = head;
		while (pi && pi->next) {
			if (pi->val==pi->next->val) {
				ListNode* del = pi->next;
				pi->next = pi->next->next;
				delete del;
			}
			else {
				pi = pi->next;
			}
		}
		return head;
	}
};

//Stack and queue, System Design
class backspace_string_compare {
public:
	bool backspaceCompare(string S, string T)
	{
		return build(S)==build(T);
	}

	string build(string str)
	{
		string ret;
		for (char ch : str) {
			if (ch!='#') {
				ret.push_back(ch);
			}
			else if (!ret.empty()) {
				ret.pop_back();
			}
		}
		return ret;
	}
};

class ParkingSystem {
public:
	int b, m, s;

	ParkingSystem(int big, int medium, int small)
			:b(big), m(medium), s(small) { }

	bool addCar(int carType)
	{
		if (carType==1) {
			if (b>0) {
				b--;
				return true;
			}
		}
		else if (carType==2) {
			if (m>0) {
				m--;
				return true;
			}
		}
		else if (carType==3) {
			if (s>0) {
				s--;
				return true;
			}
		}
		return false;
	}
};

class MinStack_optimal {
	stack<int> x_stack;
	stack<int> max_stack;
	int min;
	int max;
public:
	void push(int x)
	{
		if (x_stack.empty()) {
			min = x;
			max = x;
			x_stack.push(0);
			max_stack.push(0);
		}
		else {
			int compare = x-min;
			int compare_max = x-max;
			x_stack.push(compare);
			max_stack.push(compare_max);
			min = compare<0 ? x : min;
			max = compare_max>0 ? x : max;
		}
	}

	void pop()
	{
		int top = x_stack.top();
		int max_top = max_stack.top();
		min = top<0 ? (min-top) : min;
		cout << "pop! Max is:" << max << " max top is: " << max_top << endl;
		max = max_top>0 ? (max-max_top) : max;

		x_stack.pop();
		max_stack.pop();
	}

	int getMin()
	{
		return min;
	}

	int getMax()
	{
		return max;
	}

	int top()
	{
		//int save_min = this->min;
		int save_top = x_stack.top();
		this->pop();
		int res = save_top+min;
		this->push(res);
		return res;
	}
};

class MinMaxStack {//Leetcode155
	stack<int> x_stack;
	stack<int> min_stack;
	stack<int> max_stack;
public:
	MinMaxStack()
	{
		min_stack.push(INT_MAX);
		max_stack.push(INT_MIN);
	}

	void push(int x)
	{
		x_stack.push(x);
		min_stack.push(min(x, min_stack.top()));
		max_stack.push(max(x, max_stack.top()));
	}

	void pop()
	{
		x_stack.pop();
		min_stack.pop();
		max_stack.pop();
	}

	int top()
	{
		return x_stack.top();
	}

	int getMin()
	{
		return min_stack.top();
	}

	int getMax()
	{
		return max_stack.top();
	}
};

class Mystack {//Leetcode225, 用队列实现栈
public:
	queue<int> q;

	Mystack()
	{

	}

	/** Push element x onto stack. */
	void push(int x)
	{
		int n = q.size();
		q.push(x);
		for (int i = 0; i<n; i++) {
			q.push(q.front());
			q.pop();
		}

	}

	/** Removes the element on top of the stack and returns that element. */
	int pop()
	{
		int r = q.front();
		q.pop();
		return r;
	}

	/** Get the top element. */
	int top()
	{
		int r = q.front();
		return r;
	}

	/** Returns whether the stack is empty. */
	bool empty()
	{
		return q.empty();

	}
};

class MyQueue {
public:
	stack<int> stIn;
	stack<int> stout;

	/** Initialize your data structure here. */
	MyQueue()
	{

	}

	/** Push element x to the back of queue. */
	void push(int x)
	{
		stIn.push(x);
	}

	/** Removes the element from in front of queue and returns that element. */
	int pop()
	{
		// 只有当stOut为空的时候，再从stIn里导入数据（导入stIn全部数据）
		if (stout.empty()) {
			// 从stIn导入数据直到stIn为空
			while (!stIn.empty()) {
				stout.push(stIn.top());//// 因为pop函数弹出了元素res，所以再添加回去
				stIn.pop();
			}
		}
		int res = stout.top();
		stout.pop();
		return res;
	}

	/** Get the front element. */
	int peek()
	{
		int res = this->pop();
		stout.push(res);
		return res;
	}

	/** Returns whether the queue is empty. */
	bool empty()
	{
		return stIn.empty() && stout.empty();
	}
};

class MyCircularQueue {
private:
	vector<int> vec;
	int head, tail;
	int max_size;
	int cur_size;
public:
	/** Initialize your data structure here. Set the size of the queue to be k. */
	MyCircularQueue(int k)
			:max_size(k), head(0), tail(0), vec(vector<int>(k)), cur_size(0)
	{

	}

	/** Insert an element into the circular queue. Return true if the operation is successful. */
	bool enQueue(int value)
	{
		if (this->isFull()) {
			return false;
		}
		if (this->cur_size!=0) {
			// 考虑如果 这时是空队列， 那么需要再原地添加（tail不移动）， 而不需要后移位置
			this->tail = (++this->tail)%this->max_size;
		}
		this->vec[this->tail] = value;
		this->cur_size++;
		return true;
	}

	/** Delete an element from the circular queue. Return true if the operation is successful. */
	bool deQueue()
	{
		if (this->isEmpty()) {
			return false;
		}
		this->cur_size--;
		if (this->cur_size!=0) // 如果dequeue之后为空，那么head将不移动， 否则后移一位
			this->head = (++this->head)%this->max_size;

		return true;
	}

	/** Get the front item from the queue. */
	int Front()
	{
		if (this->isEmpty())
			return -1;
		return this->vec[this->head];
	}

	/** Get the last item from the queue. */
	int Rear()
	{
		if (this->isEmpty())
			return -1;
		return this->vec[this->tail];
	}

	/** Checks whether the circular queue is empty or not. */
	bool isEmpty()
	{
		if (this->cur_size==0) {
			return true;
		}
		return false;
	}

	/** Checks whether the circular queue is full or not. */
	bool isFull()
	{
		if (this->cur_size==this->max_size) {
			return true;
		}
		return false;
	}
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */
class Leetcode20 {
public:
	bool isValid(string s)
	{
		stack<int> st;
		for (int i = 0; i<s.size(); i++) {
			if (s[i]=='(') st.push(')');
			else if (s[i]=='{') st.push('}');
			else if (s[i]=='[') st.push(']');
				// 第三种情况：遍历字符串匹配的过程中，栈已经为空了，没有匹配的字符了，说明右括号没有找到对应的左括号 return false
				// 第二种情况：遍历字符串匹配的过程中，发现栈里没有我们要匹配的字符。所以return false
			else if (st.empty() || st.top()!=s[i]) return false;
			else st.pop(); // st.top() 与 s[i]相等，栈弹出元素
		}
		// 第一种情况：此时我们已经遍历完了字符串，但是栈不为空，说明有相应的左括号没有右括号来匹配，所以return false，否则就return true
		return st.empty();
	}
};

//hashset
class three_sum {//threesum
public:
	vector<vector<int>> threesum(vector<int>& nums)
	{
		vector<vector<int>> result;
		sort(nums.begin(), nums.end());
		for (int i = 0; i<nums.size(); i++) {
			if (nums[i]>0) {
				return result;
			}
			if (i>0 && nums[i]==nums[i-1]) {
				continue;
			}
			int left = i+1;
			int right = nums.size()-1;
			while (right>left) {

				if (nums[i]+nums[left]+nums[right]>0) {
					right--;
				}
				else if (nums[i]+nums[left]+nums[right]<0) {
					left++;
				}
				else {
					result.push_back(vector<int>{ nums[i], nums[left], nums[right] });
					while (right>left && nums[right]==nums[right-1]) {
						right--;
					}
					while (right>left && nums[left]==nums[left+1]) {
						left++;
					}
					right--;
					left++;
				}
			}
		}
		return result;
	}
};

class two_sum {//twosum
public:
	vector<int> twosum(vector<int>& nums, int target)
	{
		unordered_map<int, int> hashtable;
		for (int i = 0; i<nums.size(); i++) {
			auto it = hashtable.find(target-nums[i]);
			if (it!=hashtable.end()) {
				return { it->second, i };
			}
			hashtable[nums[i]] = i;
		}
		return {};
	}
};

class Leetcode611 {//number of tuple that can form a triangle in an array
public:
	int triangleNumber(vector<int>& nums)
	{
		if (nums.size()<3) return 0;
		sort(nums.begin(), nums.end(), greater<int>());
		int res = 0;
		int N = nums.size();
		for (int i = 0; i<N-2; ++i) {
			int l = i+1;
			int r = N-1;
			while (l<r) {
				if (nums[l]+nums[r]<=nums[i]) {
					--r;
				}
				else {
					res += r-l;
					++l;
				}
			}

		}
		return res;
	}
};

class topk {//sort
public:
	static bool cmp(pair<int, int>& m, pair<int, int>& n)
	{
		return m.second>n.second;
	}

	vector<int> topk_Frequent(vector<int>& nums, int k)
	{
		unordered_map<int, int> occurrences;
		for (auto& v : nums) {
			occurrences[v]++;
		}

		// pair 的第一个元素代表数组的值，第二个元素代表了该值出现的次数
		priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(&cmp)> q(cmp);
		for (auto& i : occurrences) {
			if (q.size()==k) {
				if (q.top().second<i.second) {
					q.pop();
					q.emplace(i.first, i.second);
				}
			}
			else {
				q.emplace(i.first, i.second);
			}
		}
		vector<int> ret;
		while (!q.empty()) {
			ret.emplace_back(q.top().first);
			q.pop();
		}
		return ret;
	}

	vector<int> getLeastNumbers(vector<int>& arr, int k)
	{
		vector<int> vec(k, 0);
		sort(arr.begin(), arr.end());
		for (int i = 0; i<k; ++i) {
			vec[i] = arr[i];
		}
		return vec;
	}

	vector<int> getLeastNumbers_heap(vector<int>& arr, int k)
	{
		vector<int> vec(k, 0);
		if (k==0) {//exclude the conditon where k is zero
			return vec;
		}
		priority_queue<int> Q;
		for (int i = 0; i<k; ++i) {
			Q.push(arr[i]);
		}
		for (int i = k; i<(int)arr.size(); ++i) {
			if (Q.top()>arr[i]) {
				Q.pop();
				Q.push(arr[i]);
			}
		}
		for (int i = 0; i<k; ++i) {
			vec[i] = Q.top();
			Q.pop();
		}
		return vec;
	}

};

class SortAlgorithm {
public:
	void mergeSort_iter(int* A, int low, int mid, int high)
	{
		int* temp = new int[high - low + 1];
		int i = low, j = mid + 1, k = 0;
		while (i <= mid && j <= high)
		{
			if (A[i] < A[j])
				temp[k++] = A[i++];
			else
				temp[k++] = A[j++];
		}
		while (i <= mid)
		{
			temp[k++] = A[i++];
		}
		while (j <= high)
		{
			temp[k++] = A[j++];
		}
		for (int i = low, k = 0; i <= high; i++, k++)
			A[i] = temp[k];
		delete[]temp;
	}
	void Merge_iter(int* A, int n)
	{
		int size = 1, low, high, mid;
		while (size <= n - 1)
		{
			low = 0;
			while (low + size <= n - 1)
			{
				mid = low + size - 1;
				high = mid + size;
				if (high > n - 1)
					high = n - 1;
				mergeSort_iter(A, low, mid, high);
				low = high + 1;
			}
			size *= 2;
		}
	}
	vector<int> sortArray(vector<int>& nums) {//归并排序
		int left=0;
		int right=nums.size()-1;
		MergeSort(nums,left,right);
		return nums;
	}
	void MergeSort(vector<int>&nums,int left,int right)
	{
		if(left<right)//只要left<right，最终情况是left=right，即数组长度为1，单独一个数，肯定是有序的
		{
			int mid=(left+right)/2;//取中点
			cout << "merge_left: " << nums[left] << " " << nums[mid]<<endl;
			MergeSort(nums,left,mid);//左边块递归排序
			cout << "merge_right: " << nums[mid+1] << " " << nums[right]<<endl;
			MergeSort(nums,mid+1,right);
			cout << "merge: " << nums[left] << " " << nums[mid] << " " << nums[mid+1] << " " << nums[right]<<endl;
			Merge(nums,left,mid,mid+1,right);//左右块合并
		}
	}
	void Merge(vector<int>&nums,int L1,int R1,int L2,int R2)//L1,R1是第一块的左右索引，L2R2同理，将两个块合并
	{
		int size = R2-L1+1;
		int *temp=new int[size];//存放合并后的有序数组（这里没用vector，用了会提示内存不足）
		int i=L1;
		int j=L2;
		int k=0;
		while(i<=R1 && j<=R2){
			if(nums[i]<nums[j])
			{
				temp[k++]=nums[i++];
			}
			else
			{
				temp[k++]=nums[j++];
			}
		}//while结束之后若有某块没遍历完（另一块肯定已经遍历完），剩下的数直接赋值
		while(i<=R1) temp[k++]=nums[i++];
		while(j<=R2) temp[k++]=nums[j++];
		for(int i=0;i<k;i++)//合并后的数赋值回原来的数组
			nums[L1+i]=temp[i];
	}
	int parititon(vector<int>& vi, int low, int up)
	{
		int pivot = vi[up];
		int i = low-1;
		for (int j = low; j<up; j++) {
			if (vi[j]<=pivot) {
				i++;
				swap(vi[i], vi[j]);
			}
		}
		swap(vi[i+1], vi[up]);
		return i+1;

	}

	void quickSort(vector<int>& vi, int low, int up)
	{
		if (low<up) {
			int mid = SortAlgorithm::parititon(vi, low, up);
			//Watch out! The mid position is on the place, so we don't need to consider it again.
			//That's why below is mid-1, not mid! Otherwise it will occur overflow error!!!
			quickSort(vi, low, mid-1);
			quickSort(vi, mid+1, up);

		}
	}

	void qSort(vector<int>& vi)
	{
		quickSort(vi, 0, vi.size()-1);
	}
};

ostream& operator<<(ostream& str, const vector<int>& arr)
{
	str << "<";
	for (auto const& i : arr) {
		str << " " << i;
	}
	str << " >";
	return str;
}

ostream& operator<<(ostream& str, const vector<string>& arr)
{
	str << "<";
	for (auto const& i : arr) {
		str << " " << i;
	}
	str << " >";
	return str;
}

template<class T>
ostream& operator<<(ostream& str, const vector<T>& vec)
{
	str << "<";
	for (auto const& i : vec) {
		str << " " << i;
	}
	str << " >";
	return str;
}

//some backtrack problems
class num_of_islands {
private:
	void dfs(vector<vector<char>>& grid, int r, int c)
	{
		//为了求出岛屿的数量，我们可以扫描整个二维网格。如果一个位置为 11，
		//则以其为起始节点开始进行深度优先搜索。在深度优先搜索的过程中，
		//每个搜索到的 11 都会被重新标记为 00。
		//最终岛屿的数量就是我们进行深度优先搜索的次数。
		int nr = grid.size();
		int nc = grid[0].size();

		grid[r][c] = '0';
		if (r-1>=0 && grid[r-1][c]=='1')dfs(grid, r-1, c);
		if (r+1<nr && grid[r+1][c]=='1')dfs(grid, r+1, c);
		if (c-1>=0 && grid[r][c-1]=='1')dfs(grid, r, c+1);
		if (c+1<nc && grid[r][c+1]=='1')dfs(grid, r, c+1);
	}

public:
	int numofislands(vector<vector<char>>& grid)
	{
		int nr = grid.size();
		if (!nr) return 0;
		int nc = grid[0].size();

		int num_islands = 0;
		for (int r = 0; r<nr; ++r) {
			for (int c = 0; c<nc; ++c) {
				if (grid[r][c]=='1') {
					++num_islands;
					dfs(grid, r, c);
				}
			}
		}
		return num_islands;
		//时间复杂度：O(MN)，其中 MM 和 NN 分别为行数和列数。

		//空间复杂度：O(MN)，在最坏情况下，整个网格均为陆地，深度优先搜索的深度达到 M NMN。
	}

	int numofislands_bfs(vector<vector<char>>& grid)
	{
		int nr = grid.size();
		if (!nr) return 0;
		int nc = grid[0].size();
		//同样地，我们也可以使用广度优先搜索代替深度优先搜索。

		//	为了求出岛屿的数量，我们可以扫描整个二维网格。如果一个位置为 11，则将其加入队列，开始进行广度优先搜索。在广度优先搜索的过程中，每个搜索到的 11 都会被重新标记为 00。直到队列为空，搜索结束。

		//	最终岛屿的数量就是我们进行广度优先搜索的次数。
		//	复杂度分析

		//	时间复杂度：O(MN)O(MN)，其中 MM 和 NN 分别为行数和列数。

		//	空间复杂度：O(\min(M, N))O(min(M, N))，在最坏情况下，整个网格均为陆地，队列的大小可以达到 \min(M, N)min(M, N)。



		int num_islands = 0;
		for (int r = 0; r<nr; ++r) {
			for (int c = 0; c<nc; ++c) {
				if (grid[r][c]=='1') {
					++num_islands;
					grid[r][c] = '0';
					queue<pair<int, int>> neighbors;
					neighbors.push({ r, c });
					while (!neighbors.empty()) {
						auto rc = neighbors.front();
						neighbors.pop();
						int row = rc.first, col = rc.second;
						if (row-1>=0 && grid[row-1][col]=='1') {
							neighbors.push({ row-1, col });
							grid[row-1][col] = '0';
						}
						if (row+1<nr && grid[row+1][col]=='1') {
							neighbors.push({ row+1, col });
							grid[row+1][col] = '0';
						}
						if (col-1>=0 && grid[row][col-1]=='1') {
							neighbors.push({ row, col-1 });
							grid[row][col-1] = '0';
						}
						if (col+1<nc && grid[row][col+1]=='1') {
							neighbors.push({ row, col+1 });
							grid[row][col+1] = '0';
						}
					}
				}
			}
		}

		return num_islands;
	}
};

class n_queens {
private:
	vector<vector<string>> result;

	void backtracking(int n, int row, vector<string>& chessboard)
	{
		if (row==n) {
			result.push_back(chessboard);
			return;
		}
		for (int col = 0; col<n; col++) {
			if (isValid(row, col, chessboard, n)) {
				chessboard[row][col] = 'Q';
				backtracking(n, row+1, chessboard);
				chessboard[row][col] = '.'; // 回溯，撤销皇后
			}
		}
	}

	bool isValid(int row, int col, vector<string>& chessboard, int n)
	{
		int count = 0;
		for (int i = 0; i<row; i++) {
			if (chessboard[i][col]=='Q') {
				return false;
			}
		}
		for (int i = row-1, j = col-1; i>=0 && j>=0; i--, j--) {
			if (chessboard[i][j]=='Q') {
				return false;
			}
		}
		for (int i = row-1, j = col+1; i>=0 && j<n; i--, j++) {
			if (chessboard[i][j]=='Q') {
				return false;
			}
		}
		return true;
	}

public:
	vector<vector<string>> solveNQueens(int n)
	{
		result.clear();
		std::vector<std::string> chessboard(n, std::string(n, '.'));
		backtracking(n, 0, chessboard);
		return result;
	}

};

class combinations {//leetcode77
	/*给定两个整数 n 和 k，返回 1 ... n 中所有可能的 k 个数的组合。*/
private:
	vector<vector<int>> result;
	vector<int> path;

	void backtracking(int n, int k, int startIndex)
	{
		if (path.size()==k) {
			result.push_back(path);
			return;
		}
		for (int i = startIndex; i<=n; i++) {
			path.push_back(i);
			backtracking(n, k, i+1);
			path.pop_back();
		}
	}

public:
	vector<vector<int>> combine(int n, int k)
	{
		result.clear();
		path.clear();
		backtracking(n, k, 1);
		return result;
	}
};

//some Greedy Problems
class wiggle_subsequence {
public:
	int wiggleMaxLength(vector<int>& nums)
	{

		if (nums.size()<=1) return nums.size();
		int curDiff = 0;// 当前一对差值
		int preDiff = 0;// 前一对差值
		int result = 1;// 记录峰值个数，序列默认序列最右边有一个峰值
		for (int i = 1; i<nums.size(); i++) {
			curDiff = nums[i]-nums[i-1];
			// 出现峰值
			if ((curDiff>0 && preDiff<=0) || (preDiff>=0) && (curDiff<0)) {
				result++;
				preDiff = curDiff;
			}
		}
		return result;
	}

};

class Distribute_candy {//Leetcode 135
public:
	int candy(vector<int>& ratings)
	{
		int size = ratings.size();
		if (size<2) {
			return size;
		}
		vector<int> num(size, 1);
		for (int i = 1; i<size; i++) {//left to right
			if (ratings[i]>ratings[i-1]) {
				num[i] = num[i-1]+1;
			}
		}
		for (int j = size-1; j>0; j--) {
			if (ratings[j]<ratings[j-1]) {
				num[j-1] = max(num[j-1], num[j]+1);
			}
		}
		int sum = 0;
		for (auto const& i : num) {
			sum += i;
		}
		return sum;
	}
};

class meeting_room {
	//输入：intervals = [[0, 30], [5, 10], [15, 20]]
	//	输出：false
public:
	static bool cmp1(const vector<int>& a, const vector<int>& b)
	{
		return a[0]<b[0];
	}

	bool canAttendMeetings(vector<vector<int>>& intervals)
	{
		int n = intervals.size();
		sort(intervals.begin(), intervals.end(), cmp1);
		for (int i = 1; i<n; i++) {
			if (intervals[i-1][1]>intervals[i][0]) {
				return false;
			}
		}
		return true;
	}
};

class meeting_room2 {
	//输入：intervals = [[0, 30], [5, 10], [15, 20]]
	//输出：2
public:
	int min_MeetingRoom(vector<vector<int>>& intervals)
	{
		int n = intervals.size();
		if (n==0) {
			return 0;
		}
		priority_queue<int, vector<int>, greater<int>> minheap_room;
		sort(intervals.begin(), intervals.end());
		minheap_room.push(intervals[0][1]);
		for (int i = 1; i<n; i++) {
			if (intervals[i][0]>=minheap_room.top()) {
				minheap_room.pop();
				minheap_room.push(intervals[i][1]);
			}
			else {
				minheap_room.push(intervals[i][1]);
			}
		}
		return minheap_room.size();
	}
};

class assign_cookies {
public:
	int find_ContentChildren(vector<int>& g, vector<int>& s)
	{
		sort(g.begin(), g.end());
		sort(s.begin(), s.end());
		int index = s.size()-1;// 饼干数组的下表
		int result = 0;
		for (int i = g.size()-1; i>=0; i--) {
			if (index>=0 && s[index]>=g[i]) {
				result++;
				index--;
			}
		}
		return result;
	}
};

class merge_intervals {
public:
	static bool cmp(const vector<int>& a, const vector<int>& b)
	{
		return a[0]<b[0];
	}

	vector<vector<int>> merge(vector<vector<int>>& intervals)
	{
		vector<vector<int>> result;
		if (intervals.size()==0) return result;
		sort(intervals.begin(), intervals.end(), cmp);
		bool flag = false;// 标记最后一个区间有没有合并
		int length = intervals.size();
		for (int i = 1; i<length; i++) {
			int start = intervals[i-1][0]; // 初始为i-1区间的左边界
			int end = intervals[i-1][1]; // 初始i-1区间的右边界
			while (i<length && intervals[i][0]<=end) {// 合并区间
				end = max(end, intervals[i][1]);// 不断更新右区间
				if (i==length-1) flag = true;// 最后一个区间也合并了
				i++;// 继续合并下一个区间
			}
			// start和end是表示intervals[i - 1]的左边界右边界，
			// 所以最优intervals[i]区间是否合并了要标记一下
			result.push_back({ start, end });
		}
		// 如果最后一个区间没有合并，将其加入result
		if (flag==false) {
			result.push_back({ intervals[length-1][0], intervals[length-1][1] });
		}
		return result;
	}

	vector<vector<int>> merge_optimized(vector<vector<int>>& intervals)
	{
		vector<vector<int>> result;
		if (intervals.size()==0) return result;
		sort(intervals.begin(), intervals.end(), [](const vector<int>& a,
				const vector<int>& b) {
		  return a[0]<b[0];
		});
		result.push_back(intervals[0]);
		for (int i = 1; i<intervals.size(); i++) {
			if (result.back()[1]>=intervals[i][0]) {// 合并区间
				result.back()[1] = max(result.back()[1], intervals[i][1]);
			}
			else {
				result.push_back(intervals[i]);
			}
		}
		return result;
	}
};

class maximum_subArray {//最大子序和
public:
	int maxSubArray_bruteForce(vector<int>& nums)
	{
		int result = INT32_MIN;
		int count = 0;
		for (int i = 0; i<nums.size(); i++) {
			count = 0;
			for (int j = i; j<nums.size(); j++) {
				count += nums[j];
				result = count>result ? count : result;
			}
		}
		return result;
	}

	int maxSubArray_Greedy(vector<int>& nums)
	{
		int result = INT32_MIN;
		int count = 0;
		for (int i = 0; i<nums.size(); i++) {
			count += nums[i];
			if (count>result) {
				result = count;
			}
			if (count<=0) count = 0;
		}
		return result;
	}
};

class BuyStock {
public:
	int maxProfit_single(vector<int>& prices)
	{//单次交易
		int inf = 1e9;
		int minprice = inf, maxprofit = 0;
		for (int price : prices) {
			maxprofit = max(maxprofit, price-minprice);
			minprice = min(price, minprice);
		}
		return maxprofit;
	}

	int maxProfit(vector<int>& prices)
	{//多次交易版
		int result = 0;
		for (int i = 1; i<prices.size(); i++) {
			result += max(prices[i]-prices[i-1], 0);
		}
		return result;
	}
};

shared_ptr<int> Copy(shared_ptr<int> sp)
{
	shared_ptr<int> a = move(sp);
	return shared_ptr<int>(a);
}

class Singleton {
private:
	Singleton();//set to private, or compiler will generate as public
	Singleton(const Singleton& other);

public:
	static Singleton* getInstance();

	static Singleton* m_instance;
};

Singleton* Singleton::m_instance = nullptr;//initialize static variable to null
//// thread not safe: if two threads go to if at the same time, m_instance would be created twice
//Singleton* Singleton::getInstance() {
//	if (m_instance == nullptr) {
//		m_instance = new Singleton();
//	}
//	return m_instance;
//}
////thread safe, but high cost brought by lock
//Singleton* Singleton::getInstance() {
//	mutex mtx;//?, read op does not need lock
//	mtx.lock();//huge cost when high concurrency
//	if (m_instance == nullptr) {
//		m_instance = new Singleton();
//	}
//	return m_instance;
//}

////内存读写reorder导致不安全，构造器的指令执行顺序可能不同
//Singleton* Singleton::getInstance() {
//	if (m_instance == nullptr) {//避免不是都不是null的时候进行读操作代价过高
//		mutex mtx;//?, read op does not need lock
//		mtx.lock();//huge cost when high concurrency
//		if (m_instance == nullptr) {//避免为null时两个线程同事进入到第一个if之后
//			m_instance = new Singleton();//分配内存，调用构造器，赋值地址？
//			//分配内存，赋值地址，调用构造器导致reorder
//		}
//	}
//	return m_instance;
//}
class LCS {//最长子序列
public:
	int longestCommonSubsequence(string text1, string text2)
	{
		const int rows = text1.size();
		const int cols = text2.size();
		vector<vector<int>> dp(rows, vector<int>(cols, 0));
		// 求解边界 BEGIN
		if (text1[0]==text2[0])
			dp[0][0] = 1;
		for (int i = 1; i<rows; i++) {
			dp[i][0] = dp[i-1][0];
			if (text1[i]==text2[0]) {
				dp[i][0] = 1;
			}
		}
		for (int j = 1; j<cols; j++) {
			dp[0][j] = dp[0][j-1];
			if (text1[0]==text2[j]) {
				dp[0][j] = 1;
			}
		}
		// 求解边界 END

		for (int i = 1; i<rows; i++)
			for (int j = 1; j<cols; j++) {
				if (text1[i]==text2[j]) { // 遇到匹配字符
					dp[i][j] = dp[i-1][j-1]+1;
				}
				else { // 不匹配时，继承左上中的较大值
					dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
				}
			}
		return dp[rows-1][cols-1];
	}

	int LongestCommonSubstring(string s1, string s2)
	{
		if (s1=="" || s2=="") {
			return 0;
		}
		int m = s1.size();
		int n = s2.size();
		vector<vector<int>> table(m+1, vector<int>(n+1));

		int biggest = 0;// 记录表中最大值
		for (int i = 0; i<m+1; ++i) {
			for (int j = 0; j<n+1; ++j) {
				if (i==0 || j==0) {
					table[i][j] = 0;
				}
				else if (s1[i-1]==s2[j-1]) {
					table[i][j] = table[i-1][j-1]+1;
					if (table[i][j]>biggest) {
						biggest = table[i][j];
					}
				}
				else {
					table[i][j] = 0;
				}
			}
		}
		return biggest;
	}

	void printLCString(string s1, string s2)
	{
		if (s1=="" || s2=="")
			return;

		int m = s1.size();
		int n = s2.size();
		vector<vector<int> > table(m+1, vector<int>(n+1));

		int biggest = 0;  // 记录表中最大值
		vector<pair<int, int> > firstPos;  // 记录子串开始的坐标
		for (int i = 0; i<m+1; ++i) {
			for (int j = 0; j<n+1; ++j) {
				// 第一行和第一列置0
				if (i==0 || j==0)
					table[i][j] = 0;
				else if (s1[i-1]==s2[j-1]) {
					table[i][j] = table[i-1][j-1]+1;
					if (table[i][j]>biggest)
						biggest = table[i][j];
					if (table[i][j]==1)
						firstPos.push_back(make_pair(i, j));
				}
				else  // 不相等置0
					table[i][j] = 0;
			}
		}

		// 输出所有的最长公共子串
		vector<pair<int, int> >::iterator beg = firstPos.begin();
		for (; beg!=firstPos.end(); ++beg) {
			int start1 = beg->first-1;
			int start2 = beg->second-1;
			if (s1.substr(start1, biggest)==s2.substr(start2, biggest))
				cout << s1.substr(start1, biggest) << endl;
		}
	}
};

class trappingRainWater {
public:
	int trap(vector<int>& height)
	{
		if (height.empty()) {
			return 0;
		}
		int ans = 0;
		int size = height.size();
		vector<int> left_max(size);
		vector<int> right_max(size);
		left_max[0] = height[0];
		for (int i = 1; i<size; i++) {
			left_max[i] = max(height[i], left_max[i-1]);
		}
		right_max[size-1] = height[size-1];
		for (int i = size-2; i>=0; i--) {
			right_max[i] = max(height[i], right_max[i+1]);
		}
		for (int i = 1; i<size-1; i++) {
			ans += min(left_max[i], right_max[i])-height[i];
		}
		return ans;

	}
};

class LongestSubstringLength {//3. 无重复字符的最长子串
public:
	int LengthofLongestSubstring(string s)
	{
		// 哈希集合，记录每个字符是否出现过
		unordered_set<char> occ;
		int n = s.size();
		// 右指针，初始值为 -1，相当于我们在字符串的左边界的左侧，还没有开始移动
		int rk = -1, ans = 0;
		// 枚举左指针的位置，初始值隐性地表示为 -1
		for (int i = 0; i<n; ++i) {
			if (i!=0) {
				// 左指针向右移动一格，移除一个字符
				occ.erase(s[i-1]);
			}
			while (rk+1<n && !occ.count(s[rk+1])) {
				// 不断地移动右指针
				occ.insert(s[rk+1]);
				++rk;
			}
			// 第 i 到 rk 个字符是一个极长的无重复字符子串
			ans = max(ans, rk-i+1);
		}
		return ans;
	}
};

class MoreThanHalf {//数组中出现次数超过一半的数字
public:
	int major_element(vector<int>& nums)
	{
		unordered_map<int, int> match;
		int len = nums.size();
		int res = 0;
		if (len==1 || len==2) {
			return nums[0];
		}
		for (int i = 0; i<len; i++) {
			match[nums[i]]++;
			if (match[nums[i]]>(len/2)) {
				res = nums[i];
				break;
			}
		}
		return res;
	}

	int major_element_vote(vector<int>& nums)
	{
		int x = 0;
		int votes = 0;
		for (int num : nums) {
			if (votes==0) x = num;
			votes += num==x ? 1 : -1;
		}
		return x;

	}
};

class medianFinder {
	priority_queue<int> lo; //max heap
	priority_queue<int, vector<int>, greater<int>> hi; //min heap
public:
	void addNum(int num)
	{
		lo.push(num);// Add to max heap

		hi.push(lo.top());// balancing step
		lo.pop();

		if (lo.size()<hi.size()) {                     // maintain size property
			lo.push(hi.top());
			hi.pop();
		}

	}

	double findMedian()
	{
		return lo.size()>hi.size() ? (double)lo.top() : (lo.top()+hi.top())*0.5;
	}

};

class QuickSortLL {
public:
	ListNode* quickSortList(ListNode* head)
	{
		// IMPORTANT: Please reset any member data you declared, as
		// the same Solution instance will be reused for each test case.
		//链表快速排序
		if (head==NULL || head->next==NULL)return head;
		ListNode tmpHead(0);
		tmpHead.next = head;
		qsortList(&tmpHead, head, NULL);
		return tmpHead.next;
	}

	void qsortList(ListNode* headPre, ListNode* head, ListNode* tail)
	{
		//链表范围是[low, high)
		if (head!=tail && head->next!=tail) {
			ListNode* mid = partitionList(headPre, head, tail);//注意这里head可能不再指向链表头了
			qsortList(headPre, headPre->next, mid);
			qsortList(mid, mid->next, tail);
		}
	}

	ListNode* partitionList(ListNode* lowPre, ListNode* low, ListNode* high)
	{
		//链表范围是[low, high)
		int key = low->val;
		ListNode node1(0), node2(0);//比key小的链的头结点，比key大的链的头结点
		ListNode* little = &node1, * big = &node2;
		for (ListNode* i = low->next; i!=high; i = i->next)
			if (i->val<key) {
				little->next = i;
				little = i;
			}
			else {
				big->next = i;
				big = i;
			}
		big->next = high;//保证子链表[low,high)和后面的部分连接
		little->next = low;
		low->next = node2.next;
		lowPre->next = node1.next;//为了保证子链表[low,high)和前面的部分连接
		return low;
	}
};

class ReverseKGroup {
public:
	pair<ListNode*, ListNode*> myReverse(ListNode* head, ListNode* tail)
	{
		ListNode* prev = tail->next;
		ListNode* p = head;
		while (prev!=tail) {
			ListNode* nex = p->next;
			p->next = prev;
			prev = p;
			p = nex;
		}
		return { tail, head };
	}

	ListNode* reverseKGroup(ListNode* head, int k)
	{
		ListNode* hair = new ListNode(0);
		hair->next = head;
		ListNode* pre = hair;

		while (head) {
			ListNode* tail = pre;
			for (int i = 0; i<k; ++i) {
				tail = tail->next;
				if (!tail) {
					return hair->next;
				}
			}
			ListNode* nex = tail->next;
			pair<ListNode*, ListNode*> result = myReverse(head, tail);
			head = result.first;
			tail = result.second;
			pre->next = head;
			tail->next = nex;
			pre = tail;
			head = tail->next;
		}
		return hair->next;
	}
};

class LongestIncreasingSubsequence {
public:
	int lengthofLIS(vector<int>& nums)
	{
		int n = (int)nums.size();
		if (n==0) return 0;
		vector<int> dp(n, 0);
		for (int i = 0; i<n; ++i) {
			dp[i] = 1;
			for (int j = 0; j<i; ++j) {
				if (nums[j]<nums[i]) {
					dp[i] = max(dp[i], dp[j]+1);
				}
			}
		}
		return *max_element(dp.begin(), dp.end());
	}

};

class reversewords {
public:
	string reverseWords(string s)
	{
		string str;
		if (s.empty())  //输入字符为空，返回空
			return str;
		cout << s.size() << endl;
		int i{ 0 }, j{ 0 };  //i，j用来表示单词开始和结束的位置
		j = s.size()-1;
		for (j; j>=0; --j) {
			if (s[j]!=' ')  //遇到不是空格的
			{
				i = j;
				while (i>=0 && s[i]!=' ')  //从j开始向左寻找单词，i>=0防止越界访问
					--i;
				for (int k = i+1; k<=j; ++k)  //单词序列加入字符串中
					str.push_back(s[k]);
				str.push_back(' ');  //加入一个空格
				j = i;  //改变j的位置
			}
		}
		if (str.size()>0)
			str.pop_back();  //移除末尾空格
		return str;
	}
};

//Amazon OA Question 1 :
//Imagine that an employment tree represents the formal employee hierarchy at Amazon.Manager nodes have
//chid nodes for each employee that reports to them; each of these employees can, in turn, have child nodes
//representing their respective reportees.Each node in the tree contains an integer representing the number of
//months the employee has spent at the company.Team tenure is computed as the average tenure of the manager
//and all the company employees working below the manager.The oldest team has the highest team tenure.
//
//Write an algorithm to find the manager of the team with the highest tenure.An employee must have child nodes
//to be a manager.
//
//Input
//The input to the function / method consists of an argument -
//president, a node representing the root node of the employee hierarchy.
//
//Output
//Return the node which has the oldest team.
//
//Note
//There will be at least one child node in the treeand there will be no ties.
//
//Example
//
//Input
//President =
//20
//12            18
//
//11   2   3      15   8
//
//Output = 18
//Explanation :
//There are three managers in this tree with the following team tenures :
//12 = > (11 + 2 + 3 + 12) / 4 = 7
//18 = > (18 + 15 + 8) / 3 = 13.67
//20 = > (12 + 11 + 2 + 3 + 18 + 15 + 8 + 20) / 8 = 11.125
struct EmployeeNode {
	int val;
	vector<EmployeeNode*> children;

	explicit EmployeeNode(int v)
			:val(v) { }
};

pair<double, int> FindMaxTenure(EmployeeNode* employee, pair<double, int>& max_team_tenure)
{

	if (size(employee->children)==0) {
		return { employee->val, 1.0 };
	}

	int total_tenure = employee->val;
	int total_employees = 1;

	for (int i = 0; i<size(employee->children); ++i) {
		pair<double, int> p1 = make_pair(FindMaxTenure(employee->children[i], max_team_tenure).first,
				FindMaxTenure(employee->children[i], max_team_tenure).second);
		total_tenure += p1.first;
		total_employees += p1.second;
	}
	double avg = total_tenure/static_cast<double>(total_employees);

	// check if team tenure is higher than current max tenure
	if (avg>max_team_tenure.first) {
		max_team_tenure.first = avg;
		max_team_tenure.second = employee->val;
	}
	return { total_tenure, total_employees };
}

EmployeeNode* MakeEmploymentTree()
{
	auto tree = new EmployeeNode(20);
	tree->children.emplace_back(new EmployeeNode(12));
	tree->children[0]->children.emplace_back(new EmployeeNode(11));
	tree->children[0]->children.emplace_back(new EmployeeNode(2));
	tree->children[0]->children.emplace_back(new EmployeeNode(3));
	tree->children.emplace_back(new EmployeeNode(18));
	tree->children[1]->children.emplace_back(new EmployeeNode(15));
	tree->children[1]->children.emplace_back(new EmployeeNode(8));
	return tree;
}

int GetMaxTeamTenure(EmployeeNode* employee)
{
	pair<double, int> max_team_tenure{/* tenure = */ 0, /* manager = */ 0 };
	FindMaxTenure(employee, max_team_tenure);
	return max_team_tenure.second;
}

pair<int, int> fill_truck(int num, vector<int> packspace)
{
	pair<int, int> res;
	for (int i = 0; i<packspace.size(); i++) {
		for (int j = i+1; j<packspace.size(); j++) {
			if (packspace[i]+packspace[j]==num-30) {
				res = make_pair(i, j);
			}
		}
	}
	return res;
}

//amazon oa
//rotting orange?
//bfs
//在给定的网格中，每个单元格可以有以下三个值之一：
//
//值 0 代表空单元格；
//值 1 代表新鲜橘子；
//值 2 代表腐烂的橘子。
//每分钟，任何与腐烂的橘子（在 4 个正方向上）相邻的新鲜橘子都会腐烂。
//
//返回直到单元格中没有新鲜橘子为止所必须经过的最小分钟数。如果不可能，返回  - 1
class RottingOrange {
public:
	int orangesRotting(vector<vector<int>>& grid)
	{
		int row = grid.size();
		int col = grid[0].size();
		int res = 0;
		vector<int> dx = { -1, 0, 0, 1 };//辅助定位即将被腐烂的橘子的横坐标
		vector<int> dy = { 0, 1, -1, 0 };//辅助定位即将被腐烂的橘子的纵坐标，对应构成腐烂橘子的四个污染方向
		queue<pair<int, int>> rot;
		for (int i = 0; i<row; ++i)//将腐烂橘子一一压入队列
			for (int j = 0; j<col; ++j)
				if (grid[i][j]==2)
					rot.push({ i, j });
		while (!rot.empty()) {
			int vol = rot.size();//标记队列内腐烂橘子个数
			for (int i = 0; i<vol; ++i) {
				pair<int, int> fir = rot.front();//取出首个腐烂橘子
				rot.pop();
				for (int j = 0; j<4; ++j)//进行四个方向污染
				{
					int x = fir.first+dx[j], y = fir.second+dy[j];
					if (x>=0 && x<row && y>=0 && y<col && grid[x][y]==1)//判断是否存在新鲜橘子
					{
						grid[x][y] = 2;
						rot.push({ x, y });
					}
				}
			}
			if (!rot.empty())//如果为空表示一开始就没有腐烂橘子，返回0分钟
				res++;//每次取出队列所有橘子时间加1，同时压入被污染的新一批橘子
		}
		for (int i = 0; i<row; ++i)//检查是否还有新鲜橘子
			for (int j = 0; j<col; ++j)
				if (grid[i][j]==1)
					return -1;
		return res;
	}
};

vector<string> fetchItemsToDisplay(int numOfItems,
		map<string, pair<int, int>> items,
		int sortParameter, int sortOrder,
		int itemsPerPage, int pageNumber)
{
	// WRITE YOUR CODE HERE

	vector<pair<string, pair<int, int>>> sorteditems;

	for (auto item : items) {
		sorteditems.push_back(item);
	}

	auto cmp0 = [](const pair<string, pair<int, int>>& l, const pair<string, pair<int, int>>& r) {
	  return l.first<r.first;
	};
	auto cmp1 = [](const pair<string, pair<int, int>>& l, const pair<string, pair<int, int>>& r) {
	  return l.second.first<r.second.first;
	};
	auto cmp2 = [](const pair<string, pair<int, int>>& l, const pair<string, pair<int, int>>& r) {
	  return l.second.second<r.second.second;
	};

	if (sortParameter==0) {
		sort(sorteditems.begin(), sorteditems.end(), cmp0);
	}
	else if (sortParameter==1) {
		sort(sorteditems.begin(), sorteditems.end(), cmp1);
	}
	else if (sortParameter==2) {
		sort(sorteditems.begin(), sorteditems.end(), cmp2);
	}

	vector<string> res;
	//for(auto item:sorteditems){
	//    cout<<item.first<<endl;
	//}

	//return res;


	//return res;

	if (sortOrder==0) {
		for (int i = 0; i<itemsPerPage; i++) {
			int index = pageNumber*itemsPerPage+i;

			if (index>=sorteditems.size() || index<0)
				continue;

			res.push_back(sorteditems[index].first);
		}

	}
	else if (sortOrder==1) {

		for (int i = 0; i<itemsPerPage; i++) {
			int size = sorteditems.size();

			int index = size-1-(pageNumber*itemsPerPage+i);

			if (index>=sorteditems.size() || index<0)
				continue;

			res.push_back(sorteditems[index].first);

		}
	}

	return res;

}

//amazon OA
//Question 2:
//Your team at amazon is overseeing the design of a new high - efficiency data center at HQ2.A power grid need to be generated for supplying power to N servers.All servers in the grid have to be connected such that they have access to power.The cost of connections between different servers varies.
//
//Assume that there are no ties, names of servers are unique, connections are directionless, there is at most one connection between a pair of servers, all costs are greater than zero, and a server does not connect to itself.
//
//Write an algorithm to minimize the cost of connecting all servers in the power grid.
//
//Input
//two arguments - num, an Integer representing number of connections.
//connectons, representing a list of connections where each element of the list consists of two serversand the cost of connection between the servers.
//
//Note
//The cost of connection between the servers is always greater than 0.
//
//Example
//Input
//num = 5
//
//connection =
//[[A, B, 1],
//[B, C, 4],
//[B, D, 6],
//[D, E, 5],
//[C, E, 1]]
//Output
//
//[[A, B, 1],
//[B, C, 4],
//[C, E, 1],
//[D, E, 5]]
void print2(int row)
{
	for (int i = 0; i<row; i++) {
		char ch = 'a';
		char print = ch;
		for (int j = 0; j<=i; j++) {
			cout << print++;
		}
		cout << endl;
	}
}

int count_digits(int num)
{
	int count = 0;
	int temp = num;
	while (temp!=0) {
		temp = temp/10;
		count++;
	}
	return (num%count);
}

//amazon OA connect ropes
//int minCost(int arr[], int n) {
//	priority_queue<int, vector<int>, greater<int>> pq(arr, arr + n);
//
//
//
//}
//Input:  arr = [8, 9, 10, 2, 5, 6]
//Output : The array is rotated 3 times
int findRotationCount(int arr[], int n)
{
	int low = 0, high = n-1;
	while (low<=high) {
		// if the search space is already sorted, we have
		// found the minimum element (at index `low`)
		if (arr[low]<=arr[high]) {
			return low;
		}
		int mid = (low+high)/2;
		// find the next and previous element of the `mid` element
		// (in a circular manner)
		int next = (mid+1)%n;
		int prev = (mid-1+n)%n;
		// if the `mid` element is less than both its next and previous
		// neighbor, it is the array's minimum element
		if (arr[mid]<=arr[next] && arr[mid]<=arr[prev]) {
			return mid;
		}
			// if `arr[mid…high]` is sorted, and `mid` is not the minimum element,
			// then the pivot element cannot be present in `arr[mid…high]`,
			// discard `arr[mid…high]` and search in the left half
		else if (arr[mid]<=arr[high]) {
			high = mid-1;
		}
			// if `arr[low…mid]` is sorted, then the pivot element cannot be present in it;
			// discard `arr[low…mid]` and search in the right half
		else if (arr[mid]>=arr[low]) {
			low = mid+1;
		}
	}
	return -1;
}

//amazon oa2
int maximumUnits(vector<vector<int>>& boxTypes, int truckSize)
{
	int res = 0;
	int n = boxTypes.size();
	priority_queue<pair<int, int>> q;
	for (auto& b : boxTypes) {
		q.push({ b[1], b[0] });
	}
	while (!q.empty()) {
		pair<int, int> t = q.top();
		q.pop();
		if (truckSize>t.second) {
			res += t.second*t.first;
			truckSize -= t.second;
		}
		else {
			res += truckSize*t.first;
			break;
		}
	}
	return res;
}

class turnstile {
public:
	vector<int> solve(vector<int>& t, vector<int>& dir)
	{
		queue<pair<int, int>> exit, entry;
		int N = t.size();
		vector<int> res(N);

		for (int i = 0; i<N; i++) {
			if (dir[i]==1) {
				exit.push({ t[i], i });
			}
			else {
				entry.push({ t[i], i });
			}
		}
		int ct = 0, lc = -1;
		// ct is the current time & lc indicates who used
		// turnstile in the previous second lc = -1 if none
		// used the turnstile in the last second
		while (!exit.empty() || !entry.empty()) {//the while loop will be executed till two queues are empty
			// checking for exit queue
			if (!exit.empty() && exit.front().first<=ct &&
					(lc==1 || lc==-1 || entry.empty() || (entry.front().first>ct))) {
				res[exit.front().second] = ct;
				lc = 1;
				exit.pop();
				//for this one, if exit queue is not empty also the first element of exit queue is before current time
				//also if the previous time lc=1 meaning that it has been used as exit, it also might be that this door is not used, so it's lc is 1 or -1
				//run exit queue also include sometimes entry runs out first or it's time is larger than current time, so proceed with exit
			}
				// checking for entry queue
			else if (!entry.empty() && entry.front().first<=ct) {
				res[entry.front().second] = ct;
				lc = 0;
				entry.pop();
			}
			else {
				lc = -1;
			}

			ct++;
		}

		return res;
	}
};

//possible Microsoft interview questions...
class count_primes {
public:
	bool isPrime(int x)
	{
		for (int i = 2; i*i<=x; ++i) {
			if (x%i==0) {
				return false;
			}
		}
		return true;
	}

	int countPrimes(int n)
	{
		int ans = 0;
		for (int i = 2; i<n; ++i) {
			ans += isPrime(i);
		}
		return ans;
	}
};

class word_search {//leetcode79
	//board =
	//	[
	//		['A', 'B', 'C', 'E'],
	//		['S', 'F', 'C', 'S'],
	//		['A', 'D', 'E', 'E']
	//	]

	//给定 word = "ABCCED", 返回 true
	//给定 word = "SEE", 返回 true
	//给定 word = "ABCB", 返回 false
public:
	bool check(vector<vector<char>>& board, vector<vector<int>>& visited, int i, int j, string& s, int k)
	{
		if (board[i][j]!=s[k]) {
			return false;
		}
		else if (k==s.length()-1) {
			return true;
		}
		visited[i][j] = true;
		vector<pair<int, int>> directions{{ 0, 1 },
										  { 0, -1 },
										  { 1, 0 },
										  { -1, 0 }};
		bool result = false;
		for (const auto& dir : directions) {
			int newi = i+dir.first, newj = j+dir.second;
			if (newi>=0 && newi<board.size() && newj>=0 && newj<board[0].size()) {
				if (!visited[newi][newj]) {
					bool flag = check(board, visited, newi, newj, s, k+1);
					if (flag) {
						result = true;
						break;
					}
				}
			}
		}
		visited[i][j] = false;
		return result;
	}

	bool exist(vector<vector<char>>& board, string word)
	{
		int h = board.size(), w = board[0].size();
		vector<vector<int>> visited(h, vector<int>(w));
		for (int i = 0; i<h; i++) {
			for (int j = 0; j<w; j++) {
				bool flag = check(board, visited, i, j, word, 0);
				if (flag) {
					return true;
				}
			}
		}
		return false;
	}
};

string bool_to_string(int i)
{
	string true_{ "true" };
	string false_{ "false" };
	if (i==1) {
		return true_;
	}
	else {
		return false_;
	}
}

int main()
{
	Leetcode35 SearchInsertPosition;
	vector<int> arr{ 1, 3, 5, 6 };
	cout << "SearchInsertPosition: " << SearchInsertPosition.searchInsert(arr, 7) << endl;
	Leetcode27 RemoveElement;
	//cout << "RemoveElement: "<<RemoveElement.removeElement(arr, 3)<<endl;

	cout << "RemoveElement: " << RemoveElement.removeElementDoubleP(arr, 5) << endl;
	Leetcode209 SlidingWindow209;
	vector<int> nums{ 2, 3, 1, 2, 4, 3 };
	cout << "minSubArrayLenSlidingWindow: " << SlidingWindow209.minSubArrayLenSlidingWindow(7, nums) << endl;

	ListNode* head = new ListNode(1);
	ListNode* a = new ListNode(2);
	ListNode* b = new ListNode(6);
	ListNode* c = new ListNode(3);
	ListNode* d = new ListNode(4);
	ListNode* e = new ListNode(5);
	ListNode* f = new ListNode(6);
	head->next = a;
	a->next = b;
	b->next = c;
	c->next = d;
	d->next = e;
	e->next = f;
	cout << endl;
	Leetcode203 RemoveLLElement;
	ListNode* newHead = RemoveLLElement.removeElements(head, 6);
	printLL(newHead);
	cout << endl;
	SinglyLinkedList LL{ 1, 2, 3, 4 };
	cout << LL << endl;
	ListNode* HHead = RemoveLLElement.removeElements(LL.head, 3);
	cout << LL << endl;
	Leetcode206 ReverseLL;
	ListNode* ReverseHead = ReverseLL.reverseLinkedList(LL.head);
	//while (ReverseHead) {
	//	cout << ReverseHead->val;
	//	ReverseHead = ReverseHead->next;
	//}
	printLL(ReverseHead);
	ListNode* cyclehead = new ListNode(3);
	ListNode* cycleheadA = new ListNode(0);
	ListNode* cycleheadB = new ListNode(2);
	ListNode* cycleheadC = new ListNode(-4);
	cyclehead->next = cycleheadA;
	cycleheadA->next = cycleheadB;
	cycleheadB->next = cycleheadC;
	cycleheadC->next = cycleheadA;
	Leetcode142 DetectCycle;
	cout << "Cycle Entry Point: " << DetectCycle.detectCycle(cyclehead)->val << endl;
	//printLL(cyclehead);

	Leetcode20 isvalid;
	bool is_valid = isvalid.isValid("{[]}");
	cout << "{ [] } is " << is_valid << endl;
	cout << "{{{{{ is " << isvalid.isValid("{{{{{") << endl;
	shared_ptr<int> sp1 = make_shared<int>(10);
	unique_ptr<int> p1 = make_unique<int>(5);
	shared_ptr<int> p2 = move(p1);
	Leetcode611 findTriNum;
	vector<int> Tri_Array{ 2, 2, 3, 4 };
	cout << "In array 2,2,3,4, there are " << findTriNum.triangleNumber(Tri_Array) << " triangles" << endl;
	Leetcode26 REMOVEDUP;
	vector<int> arr_removedup{ 0, 0, 1, 2, 2, 3, 3 };
	cout << "0,0,1,2,2,3,3,After remove duplicates: " << REMOVEDUP.removeDuplicates(arr_removedup) << endl;
	topk findtopk;
	vector<int> TOPK{ 3, 2, 1 };
	cout << "topk nums are " << findtopk.getLeastNumbers_heap(TOPK, 2) << endl;
	vector<int> topK_fre{ 1, 1, 1, 2, 2, 3 };
	cout << "Frequency top: " << findtopk.topk_Frequent(topK_fre, 2) << endl;
	vector<int> QS{ 5, 4, 3, 2, 1 };
	cout << "Before Quick Sort: " << QS << endl;
	SortAlgorithm qs;
	qs.qSort(QS);
	cout << "After Quick Sort : " << QS << endl;

	Mystack ms;
	ms.push(1);
	ms.push(2);
	ms.push(3);
	cout << "top of the stack: " << ms.top() << endl;

	MyQueue mq;
	mq.push(1);
	mq.push(2);
	mq.push(3);
	cout << "top of the queue: " << mq.peek() << endl;

	MyCircularQueue circularQueue(3);
	circularQueue.enQueue(1);
	circularQueue.enQueue(2);
	circularQueue.enQueue(3);
	circularQueue.enQueue(4);
	cout << "Rear element: " << circularQueue.Rear() << endl;
	circularQueue.isFull();
	circularQueue.deQueue();
	circularQueue.enQueue(4);
	circularQueue.Rear();
	cout << "Rear element: " << circularQueue.Rear() << endl;

	SinglyLinkedList repeated{ 1, 1, 1, 2, 2, 3, 3, 4, 4 };
	Leetcode83 RemoveRepeated;
	printLL(RemoveRepeated.deleteDuplicates(repeated.head));

	vector<int> s{ 1, 1, 1, 2, 2, 3, 3, 4, 4 };
	Leetcode384 sol = Leetcode384{ s };
	cout << "After shuffle: " << sol.shuffle() << endl;
	cout << "Original is: " << sol.reset() << endl;

	/*******************判断字典序*******************/
	int i = 0x11223344;
	char* p;

	p = (char*)&i;
	cout << *p << endl;
	if (*p==0x44) {
		printf("Little endian\n");
	}
	else {
		printf("Big endian\n");
	}
	/*******************判断字典序*******************/

	offer67 strint;
	cout << strint.strToInt("     -100") << endl;

	split Split;
	cout << Split.Split("       313413,   34324,,,,,-12432", ',') << endl;
	//string tryStr { "hello" };
	//for (auto i : tryStr) {
	//	cout << i;
	//}

	MinMaxStack minmaxstack;
	minmaxstack.push(1);
	minmaxstack.push(5);
	minmaxstack.push(6);
	minmaxstack.push(2);
	cout << "max of stack: " << minmaxstack.getMax() << endl;
	cout << "min of stack: " << minmaxstack.getMin() << endl;
	cout << endl;
	MinStack_optimal minstack_opt;
	minstack_opt.push(2);
	minstack_opt.push(1);
	minstack_opt.push(3);
	minstack_opt.push(0);
	//minstack_opt.pop();
	minstack_opt.pop();
	cout << "min of Optimal stack: " << minstack_opt.getMin() << endl;
	cout << "max of Optimal stack: " << minstack_opt.getMax() << endl;
	cout << "top of the Optimanl stack: " << minstack_opt.top() << endl;

	Distribute_candy Candy;
	vector<int> d_candy{ 1, 0, 2 };
	cout << "Distribute candy according to the ratings: " << Candy.candy(d_candy) << endl;

	cout << "gcd of 35 and 28: " << gcd(35, 28) << endl;

	//construct binary tree:
	TreeNode* root = new TreeNode(5);
	TreeNode* root_left = new TreeNode(4);
	TreeNode* root_right = new TreeNode(6);
	TreeNode* root_left_left = new TreeNode(1);
	TreeNode* root_left_right = new TreeNode(2);
	root->left = root_left;
	root->right = root_right;
	root_left->left = root_left_left;
	root_left->right = root_left_right;
	preorder Pre;
	cout << "Pre order is: " << Pre.preorder_iterative(root) << endl;
	postorder Post;
	cout << "Post order is: " << Post.postorder_iterative(root) << endl;
	inorder in;
	cout << "in order is: " << in.inorder_iterative(root) << endl;
	levelorder Level;
	zlevelorder zlevel;
	cout << "level order is: " << endl;
	for (auto const& i : Level.LevelOrder(root)) {
		cout << i << endl;
	}
	cout << "Z-level order is: " << endl;
	for (auto const& i : zlevel.zlevel(root)) {
		cout << i << endl;
	}
	//rank!
	//vector<int> ints;
	//int player;
	//int num_of_player;
	//cout << "plz input the number of the player: ";
	//cin >> num_of_player;
	//while (num_of_player>0) {
	//	cin >> player;
	//	ints.push_back(player);
	//	--num_of_player;
	//}
	//topk sortrank;
	//cout << sortrank.getLeastNumbers_heap(ints, 3) << endl;
	//vector<int> rank_res = sortrank.getLeastNumbers_heap(ints, 3);
	//cout << rank_res;
	//List l(3);
	//l.traverseList();

	char ch[]{ 'M', 'A', 'X', 'H', 'U', 'B' };
	char ch1[6]{ 'M', 'A', 'X', 'H', 'U', 'B' };
	char ch2[] = "MAXHUB";
	cout << sizeof(ch) << "," << strlen(ch) << endl;
	cout << sizeof(ch1) << "," << strlen(ch1) << endl;
	cout << sizeof(ch2) << "," << strlen(ch2) << endl;

	string str = "night";
	//char* const p_str = str.c_str(); error
	//p_str[0] = 'h';
	cout << str << endl;

	char maxhub[] = "maxhub\0\0\x11\\";
	cout << sizeof(maxhub) << "," << strlen(maxhub) << "," << sizeof(maxhub+1) << endl;
	char str_[] = { 'h', 'e', 'l', 'l', 'o' };
	str_[0] = 'a';//ok
	string str2(str_);//ok

	char str__[] = "hello";
	str__[0] = 'a';

	//char *str___ = "hello";//error

	shared_ptr<int> pp1(new int(2));
	shared_ptr<int> pp2(new int(2));
	weak_ptr<int> pp3;
	pp3 = pp1;
	auto pp4 = Copy(pp2);
	cout << pp1.use_count() << "," << pp2.use_count() << "," << pp3.use_count() << "," << pp4.use_count() << endl;

	//int aa[5];
	//*(2 + aa) = 1;

	//char str____[10];
	//cin >> str____;
	//for (auto i : str____) {
	//	cout << i;
	//}
	//map<int, list<pair<int, list<course*> >*> > DB1;
	//for (auto i : DB1) {
	//	for (auto j : i.second) {
	//		for (auto h : j->second) {

	//		}
	//	}
	//}

	//map<int, map<int, list<course*>*>> DB2;
	//for (auto i : DB2) {
	//	for (auto j : i.second) {
	//		for (auto h :*j.second) {
	//			for (auto p : h) {

	//			}

	//		}

	//	}
	//}
	//map<list<string>*, int >m1;
	//for (auto i : m1) {
	//	for(auto j:*i.first)
	//}

	LCS lcs;
	cout << "Longest Common Subsequence: " << lcs.longestCommonSubsequence("abcde", "ace") << endl;
	cout << "Longest Common Substring: " << lcs.LongestCommonSubstring("abcde", "abce") << endl;
	string s1 = "hello,world,james";
	string s2 = "james is saying hello";
	cout << "Longest Common Substring: ";
	lcs.printLCString(s1, s2);

	LRUCache cache(2);
	cache.put(1, 1);
	cache.put(2, 2);
	cout << "cache get: " << cache.get(1) << endl;       // 返回  1
	cache.put(3, 3);    // 该操作会使得密钥 2 作废
	cout << "cache get: " << cache.get(2) << endl;       // 返回 -1 (未找到)
	cache.put(4, 4);    // 该操作会使得密钥 1 作废
	cache.get(1);       // 返回 -1 (未找到)
	cache.get(3);       // 返回  3
	cache.get(4);       // 返回  4

	vector<int> major_element{ 1, 2, 3, 2, 2, 2, 5, 4, 2 };
	MoreThanHalf mth;
	cout << "more than half element: " << mth.major_element(major_element) << endl;
	cout << "more than half element: " << mth.major_element_vote(major_element) << endl;

	sortLinkedList sortLL;
	SinglyLinkedList selection{ 4, 3, 2, 1 };
	ListNode* newSelectionHead = sortLL.selectSortList(selection.head);
	printLL(newSelectionHead);
	SinglyLinkedList quickSort{ 3, 1, 4, 2 };
	ListNode* newquickSortSwap_Head = sortLL.quickSortList(quickSort.head);
	printLL(newquickSortSwap_Head);

	AddtwoNumber add;
	cout << "add two num -8 and 9: " << add.add(-8, 9) << endl;

	vector<int> tryvector{ 1 };
	cout << "sizeof vector is: " << sizeof(tryvector) << endl;

	medianFinder median;
	median.addNum(41);
	median.addNum(35);
	median.addNum(62);
	median.addNum(5);
	median.addNum(97);
	median.addNum(108);
	cout << "median is: " << median.findMedian() << endl;

	trappingRainWater trap;
	vector<int> _trap{ 0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1 };
	cout << "Rain water: " << trap.trap(_trap) << endl;

	LongestSubstringLength Lsl;
	cout << "Longest Subtring Length: " << Lsl.LengthofLongestSubstring("abcabcbb") << endl;

	SinglyLinkedList reverseK{ 1, 2, 3, 4, 5, 6, 7 };
	ReverseKGroup reverseKGrp;
	ListNode* newReverseKGroupHEAD = reverseKGrp.reverseKGroup(reverseK.head, 2);
	cout << "1,2,3,4,5,6,7 reverse in group of 2 is: ";
	printLL(newReverseKGroupHEAD);
	cout << endl;

	vector<int> stock_array{ 7, 1, 5, 3, 6, 4 };
	BuyStock stock;
	cout << "maxProfit of multiple transaction is:  " << stock.maxProfit(stock_array) << endl;

	vector<int> twosum_array{ 2, 7, 11, 15 };
	two_sum twoSum;
	cout << "two sum subscript: " << twoSum.twosum(twosum_array, 9) << endl;

	vector<int> threesum_array{ -1, 0, 1, 2, -1, -4 };
	three_sum threesum;
	cout << "three sum: " << endl;
	for (auto i : threesum.threesum(threesum_array)) {
		cout << i;
	}
	cout << endl;

	TreeNode* RightSideViewRoot = new TreeNode(1);
	TreeNode* RightSideViewRoot_left = new TreeNode(2);
	TreeNode* RightSideViewRoot_right = new TreeNode(3);
	TreeNode* RightSideViewRoot_left_right = new TreeNode(5);
	TreeNode* RightSideViewRoot_right_right = new TreeNode(4);
	RightSideViewRoot->left = RightSideViewRoot_left;
	RightSideViewRoot->right = RightSideViewRoot_right;
	RightSideViewRoot_left->right = RightSideViewRoot_left_right;
	RightSideViewRoot_right->right = RightSideViewRoot_right_right;
	RightSide rightside;
	cout << "Right side view is: " << rightside.rightSideView(RightSideViewRoot) << endl;
	GetDepth getdepth;
	cout << "depth of binary tree: " << getdepth.maxdepth(RightSideViewRoot) << endl;
	isBinaryTreeBalanced isbalanced;
	cout << "balanced tree?: " << isbalanced.isbalanced(RightSideViewRoot) << endl;

	maximum_subArray maxsum_subarray;
	vector<int> max_subarray{ -2, 1, -3, 4, -1, 2, 1, -5, 4 };
	cout << "maxsum of subarray: " << maxsum_subarray.maxSubArray_Greedy(max_subarray) << endl;

	LongestIncreasingSubsequence LIS;
	vector<int> LongestIS{ 10, 9, 2, 5, 3, 7, 101 };
	cout << "Length of Increasing subseq: " << LIS.lengthofLIS(LongestIS) << endl;

	int A[3][5]{{ 1, 2, 3, 4, 5 },
				{ 6, 7, 8, 9, 10 },
				{ 11, 12, 13, 14, 15 }};

	cout << A[1][3] << " " << *(A[1]+3) << " " << *(*(A+1)+3) << " "
		 << *(&A[0][0]+5*1+3) << " " << *(*(A+1)) << endl;
	//char arr[] = "abcd";
	//char arr2[] = "abcd";

	//const char arr3[] = "abcd";
	//const char arr4[] = "abcd";

	///*char* arr7 = "abcd";
	//char* arr8 = "abcd";*/

	//const char* arr7 = "abcd";
	//const char* arr8 = "abcd";

	///*cout << (arr == arr2) << endl;*/
	//cout << (arr3 == arr4) << endl;
	//cout << (arr7 == arr7) << endl;
	//cout << (arr7 == arr8) << endl;

	reversewords WORDS;
	cout << WORDS.reverseWords("i love u") << endl;

	auto president = MakeEmploymentTree();
	cout << GetMaxTeamTenure(president) << '\n';

	RottingOrange ro;
	vector<vector<int>> orange{{ 2, 1, 1 },
							   { 1, 1, 0 },
							   { 0, 1, 1 }};
	cout << "{2,1,1},{1,1,0},{0,1,1}_Rotting orange approachable:" << ro.orangesRotting(orange) << endl;
	vector<vector<int>> orange_{{ 2, 1, 1 },
								{ 0, 1, 1 },
								{ 1, 0, 1 }};
	cout << "{2,1,1},{0,1,1},{1,0,1}_Rotting orange not approachable:" << ro.orangesRotting(orange_) << endl;

	print2(4);
	cout << endl;
	cout << count_digits(178) << endl;

	pair<int, int> truckRes = fill_truck(90, { 1, 10, 25, 35, 60 });
	cout << truckRes.first << truckRes.second << endl;

	int arr_rotation[] = { 8, 9, 10, 2, 5, 6 };
	int n = sizeof(arr_rotation)/sizeof(arr_rotation[0]);

	cout << "size of rotation arr: " << n << endl;

	int count_rotation = findRotationCount(arr_rotation, n);
	cout << "the array is rotated: " << count_rotation << " times" << endl;

	turnstile door;
	vector<int> turnstile_t{ 0, 0, 1, 5 };
	vector<int> turnstile_dir{ 0, 1, 1, 0 };
	vector<int> turnstile_sol = door.solve(turnstile_t, turnstile_dir);
	cout << "turnstile result: " << turnstile_sol << endl;

	vector<vector<int>> maxunit{{ 1, 3 },
								{ 2, 2 },
								{ 3, 1 }};
	int fill_truck_result = maximumUnits(maxunit, 3);
	cout << "fill truck result: " << fill_truck_result << endl;

	merge_intervals merger;
	vector<vector<int>> intervals{{ 1, 3 },
								  { 2, 6 },
								  { 8, 10 },
								  { 15, 18 }};
	vector<vector<int>> merge_result = merger.merge(intervals);
	cout << "interval" << endl;
	cout << merge_result << endl;

	combinations find_comb;
	cout << find_comb.combine(4, 2) << endl;

	wiggle_subsequence wiggleSubqe;
	vector<int> seq{ 1, 17, 5, 10, 13, 15, 10, 5, 16, 8 };
	cout << "wiggle subsequence length: " << wiggleSubqe.wiggleMaxLength(seq) << endl;

	cout << "meeting_room1 return true false" << endl;
	meeting_room meeting_room;
	vector<vector<int>> meetingroom_intervals{{ 0, 30 },
											  { 5, 10 },
											  { 15, 20 }};
	cout << meeting_room.canAttendMeetings(meetingroom_intervals) << endl;
	meetingroom_intervals = {{ 7, 10 },
							 { 2, 4 }};
	cout << meeting_room.canAttendMeetings(meetingroom_intervals) << endl;

	cout << "meeting_room2 return number of rooms" << endl;
	meeting_room2 meeting_room2;
	vector<vector<int>> meetingroom2_intervals{{ 0, 30 },
											   { 5, 10 },
											   { 15, 20 }};
	cout << meeting_room2.min_MeetingRoom(meetingroom_intervals) << endl;
	cout << meeting_room2.min_MeetingRoom(meetingroom2_intervals) << endl;

	cout << "assign_cookies: " << endl;
	assign_cookies assign_cookies;
	vector<int> g{ 1, 2 };
	vector<int> ss{ 1, 2, 3 };
	cout << assign_cookies.find_ContentChildren(g, ss) << endl;

	backspace_string_compare compare_string;
	string backspace_s{ "ab#c" };
	string backspace_t{ "ad#c" };
	cout << "backspace#_string compare: ab#c,ad#c ";
	cout << bool_to_string(compare_string.backspaceCompare(backspace_s, backspace_t)) << endl;

	//board =
//	[
//		['A', 'B', 'C', 'E'],
//		['S', 'F', 'C', 'S'],
//		['A', 'D', 'E', 'E']
//	]

//给定 word = "ABCCED", 返回 true
//给定 word = "SEE", 返回 true
//给定 word = "ABCB", 返回 false
	word_search search_word;
	vector<vector<char>> board{{ 'A', 'B', 'C', 'E' },
							   { 'S', 'F', 'C', 'S' },
							   { 'A', 'D', 'E', 'E' }};
	string word_to_search{ "ABCCED" };
	cout << "search word in board: ABCCED" << endl;
	cout << bool_to_string(search_word.exist(board, word_to_search)) << endl;
	string word_to_search_{ "SEE" };
	cout << "search word in board: SEE" << endl;
	cout << bool_to_string(search_word.exist(board, word_to_search_)) << endl;
	string word_to_search__{ "ABCB" };
	cout << "search word in board: ABCB" << endl;
	cout << bool_to_string(search_word.exist(board, word_to_search__)) << endl;


	//输入：grid = [
	//	["1", "1", "0", "0", "0"],
	//		["1", "1", "0", "0", "0"],
	//		["0", "0", "1", "0", "0"],
	//		["0", "0", "0", "1", "1"]
	//]
	//	输出：3

	num_of_islands count_numofislands;
	vector<vector<char>> island_grid{{ '1', '1', '0', '0', '0' },
									 { '1', '1', '0', '0', '0' },
									 { '0', '0', '1', '0', '0' },
									 { '0', '0', '0', '1', '1' }};
	cout << "num of islands in the grid: ";
	cout << count_numofislands.numofislands(island_grid) << endl;
	vector<vector<char>> island_grid_bfs{{ '1', '1', '0', '0', '0' },
										 { '1', '1', '0', '0', '0' },
										 { '0', '0', '1', '0', '0' },
										 { '0', '0', '0', '1', '1' }};
	cout << "num of islands in the grid: ";
	cout << count_numofislands.numofislands_bfs(island_grid_bfs) << endl;

	cout << "some n_queens" << endl;
	n_queens find_n_queens;
	vector<vector<string>> n_queens_res = find_n_queens.solveNQueens(6);
	for (const auto& i : n_queens_res) {
		cout << i;
		cout << endl;
	}

	count_primes count_primes;
	cout << "num of primes within 10 is: " << count_primes.countPrimes(10) << endl;

	MergeSortedArray merge_sorted_array;
	vector<int> merge_a{ 1, 2, 3, 0, 0, 0 };
	vector<int> merge_b{ 2, 5, 6 };
	merge_sorted_array.merge(merge_a, 3, merge_b, 3);
	cout << "merge_sorted_array: " << merge_a << endl;

	//merge_k_sorted_LL
	SinglyLinkedList LL1{ 1, 2, 3, 4 };
	SinglyLinkedList LL2{ 2, 3, 4 };
	SinglyLinkedList LL3{ 4, 5, 6, 7 };
	merge_K_sorted_LL merge_k;
	vector<ListNode*> LL_Heads;
	LL_Heads.push_back(LL1.head);
	LL_Heads.push_back(LL2.head);
	LL_Heads.push_back(LL3.head);
	cout << "merge_K_sorted_LL: ";
	ListNode* k_sortedLL_head = merge_k.mergeK_LinkedList_priorityqueue(LL_Heads);
	//ListNode* k_sortedLL_head_pri=merge_k.mergeK_LinkedList_priorityqueue(LL_Heads);
	//cout << k_sortedLL_head->val<<endl;
	while (k_sortedLL_head) {
		cout << k_sortedLL_head->val;
		cout << " ";
		k_sortedLL_head = k_sortedLL_head->next;
	}
	cout << endl;


	//merge_sort_recursion

	vector<int> merge_sort_vec{5,1,3,2,0,0,4,7};
	cout << endl << "merge_sort_recursion: " << merge_sort_vec << endl;
	vector<int> merge_sort_res = qs.sortArray(merge_sort_vec);
	cout << merge_sort_vec << endl;

	//merge_sort_iteration
	int merge_sort_array[8]={1, 4, 6,8, 3,4, 5,1};
	int array_len = sizeof(merge_sort_array)/sizeof(merge_sort_array[0]);
	qs.Merge_iter(merge_sort_array,array_len);
	for (int i = 0; i<array_len;i++) {
		cout << merge_sort_array[i]<<" ";
	}


	//copy_random_List, deep_copy
	cout << endl<<"copy_random_list: ";
	copy_random_List cp_rand;
	Node_class* node_class_head = new Node_class(7);
	Node_class* node_class_1 = new Node_class(13);
	Node_class* node_class_2 = new Node_class(11);
	Node_class* node_class_3 = new Node_class(10);
	Node_class* node_class_4 = new Node_class(1);
	node_class_head->next = node_class_1;
	node_class_1->next = node_class_2;
	node_class_2->next = node_class_3;
	node_class_3->next = node_class_4;
	node_class_4->next = nullptr;
	node_class_head->random = nullptr;
	node_class_1->random = node_class_head;
	node_class_2->random = node_class_3;
	node_class_3->random = node_class_2;
	node_class_4->random = node_class_head;
	auto* new_node_head = cp_rand.copyRandomList(node_class_head);
	while(new_node_head){
		cout << new_node_head->val << " ";
		new_node_head = new_node_head->next;
	}
	cout << endl;
	cout<<"node1's random: "<<node_class_1->random->val << endl;








}
