# data-structure
data structure practice (synchronize between two systems)

## 比较有用的点
- [throw exception](./stack/stack_list(exception).cpp)
  - 继承实现自定义Exception并实现`const cha r* what() const noexcept {}`方法实现`throw`报错并输出报错信息
- [列表初始化的实现](./queue/queue_list(initializer_list).cpp)
  - 使用`std::initializer_list<int>`的`begin()`和`end()`方法遍历初始化列表
  - 由此，也可用`for (auto val : list){}`遍历
- [自定义Iterator对象实现begin()和end()方法的遍历方式](./list/list(Iterator).cpp)
  - 实现`Iterator`类的`operator*()`，`operator++()`，`operator!=()`方法
  - 实现`begin`和`end`之后，可以使用`for (auto val : list){}`遍历
