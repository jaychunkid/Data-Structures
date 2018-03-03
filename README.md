## 数据结构
大二上学期数据结构课程的代码练习，对学到的数据结构进行简单的代码实现。<br>

### 树相关
* `GeneralTree.h`：利用数组实现简单的平凡树，数组节点存放树节点的编号。支持合并两个节点所在的树，以及判断两个节点是否在同一棵树中，应用了加权结合和路径压缩算法来降低树的高度。<br>
* `BST.h，BSTNode.h`：二叉搜索树实现，支持插入、删除、清空节点，获取对应键值的节点、树的节点数目，判断树是否为空，以及输出树的结构。<br>
* `TTTreeNode.h`，`TTTree.h`：2-3树实现，支持插入、搜索、清空节点，删除节点功能未实现。<br>
* `Heap.h`：利用数组实现小顶堆，支持向堆中插入节点，获取堆的顶部节点值，以及弹出堆的顶部节点。<br>

### 队列相关
* `List.h`：队列的抽象类，要求子类实现清空、插入、删除、尾部追加节点，队列栅栏的移动，栅栏指向节点值的获取，判断队列是否为空，以及获取队列的长度等函数。<br>
* `LinkedList.h`：队列的链表实现。<br>
* `ArrayList.h`：队列的数组实现。<br>
* `Queue.h`：先进先出队列实现，需要`LinkedList.h`头文件，支持获取首节点，弹出首节点，获取尾节点，追加尾节点，以及判断队列是否为空。<br>
* `Stack.h`：栈实现，需要`ArrayList.h`头文件，支持获取栈顶节点，弹出栈顶节点，压入节点，以及判断栈是否为空。<br>

### 图相关
* `Graph.h`：图的抽象类，以及图相关算法的声明。其中图抽象类要求子类实现获取图的节点数和边数，对图中节点进行标记，遍历节点连边，获取节点出入度、设置、删除连边，获取连边权值等功能，边的有向性可选。而图相关算法包括深度优先、广度优先遍历，拓扑排序，Floyd算法，Dijkstra算法以及Prim算法。<br>
* `GraphMatrix.h`：利用邻接矩阵（二维数组）实现图。<br>
* `GraphList.h`：利用邻接表（链表数组）实现图，需要`LinkedList.h`头文件。<br>
* `Graph.cpp`:图相关算法的实现。其中深度优先遍历需要`Stack.h`头文件，广度优先遍历、拓扑排序需要`Queue.h`头文件，Dijkstra算法和Prim算法需要`Heap.h` 头文件。<br>

### 搜索相关
* `Sort.h`：搜索算法实现（从小到大），包括插入排序，冒泡排序，选择排序，希尔排序，归并排序以及快排序。<br>


## Data Structures
Inplementations of some data structures which were learned on class.<br>

### Tree
* `GeneralTree.h`: General tree implementations with arrays. Each array element corresponds to a node of the tree. Method `differ()` checks if two objects are in different sets. Method `merge()` merges two sets together with weight union rule. Method `findRoot()` searches for the root node and applies path compression on each node passed.<br>
* `BST.h`, `BSTNode.h`: Binary Search Tree implementations. 
* `TTTreeNode.h`, `TTTree.h`: 2-3 Tree implementations. The function removing the node has not been implemented.
* `Heap.h`: Min-heap implementations with arrays. Private method `siftdown()` keep pushing down a node until it reaches a correct level.<br>

### List
* `List.h`: List abstractions. Method `curPos()`, `setPos()`, `moveToFront()`, `moveToBack()`, `getValue()`, `prev()` and `next()` operate the partition in list.<br> 
* `LinkedList.h`: List implementations with linked lists.<br>
* `ArrayList.h`: List implementations with arrays.<br>
* `Queue.h`: "First-In, First-Out" lists implementations with linked lists. Inplementations need the file `LinkedList.h`.<br>
* `Stack.h`: "Last-In, First-Out" lists implementations with array lists. Inplementations need the file `ArrayList.h`.<br>

### Graph
* `Graph.h`: Graph abstractions and graph traversal algorithm statements.<br> 
* `GraphMatrix.h`: Graph implementations with adjacency matrix.<br>
* `GraphList.h`: Graph implementations with adjacency list.<br>
* `Graph.cpp`: Graph traversal algorithm implementations. Method `DFS()`, `BFS()`, `TopSort()` are implementations for deep-first graph traversal algorithm, breadth-first graph traversal algorithm and topological sort algorithm. Method `Dijkstra()`, 
`Prim()`, `FloydWarshall()` are implementations for Dijkstra's algorithm, Prim's algorithm and Floyd's algorithm.<br>

### Sort
* `Sort.h`: Sorting algorithm implementations such as insertion sort, bubble sort, selection sort, shellsort, mergesort and quicksort.<br>
