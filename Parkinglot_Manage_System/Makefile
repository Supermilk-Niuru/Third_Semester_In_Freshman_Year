# ============================================
# 停车场管理系统 - Makefile
# 用于编译整个项目
# ============================================

# 编译器：使用 g++（C++编译器）
CXX = g++

# 编译选项：
#   -Wall  打开所有警告
#   -std=c++11  使用C++11标准
CXXFLAGS = -Wall -std=c++11

# 最终生成的可执行文件名
TARGET = parking

# 需要编译的源文件
# （Car.h 和 ParkingLot.h 是头文件，被 main.cpp 包含，不用单独编译）
SOURCES = main.cpp

# ============================================
# 默认目标：编译整个项目
# 在终端输入 make 就会执行这里
# ============================================
all: $(TARGET)

# 编译规则：把 main.cpp 编译成 parking 可执行文件
$(TARGET): $(SOURCES) Car.h ParkingLot.h
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

# 运行程序
run: $(TARGET)
	./$(TARGET)

# 清理编译生成的文件
clean:
	rm -f $(TARGET)

# 重新编译（先清理再编译）
rebuild: clean all
