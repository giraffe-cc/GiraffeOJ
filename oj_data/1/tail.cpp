
// tail.cpp 用户不可见，但是最终编译时，会把用户提交的代码和 tail.cpp 合并成一个文件再进行编译

void Test1() {
    Solution s;
    bool ret = s.isPalindrome(121);
    if (ret) {
        std::cout << "Test1 OK" << std::endl;
    }else {
        std::cout << "Test1 failed" << std::endl;
    }
}

void Test2() {
    Solution s;
    bool ret = s.isPalindrome(-121);
    if (ret) {
        std::cout << "Test2 OK" << std::endl;
    }else {
        std::cout << "Test2 failed" << std::endl;
    }

}

int main() {

}
