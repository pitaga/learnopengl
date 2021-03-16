- 配置新项目
  - C++ 空项目
  - 项目名称 —— `$(ProjectName)` 
  - 位置 —— `opengl` （此目录）
  - 解决方案名称 —— source
- 解决方案配置
  - `Debug` 模式`x64` 平台
- 项目属性配置

  - 常规
    - 输出目录 `..\..\bin`
    - 中间目录 `..\..\temp`
  - `VC++` 目录
    - 包含目录 —— `..\..\depend\include` 
    - 库目录 —— `..\..\depend\lib` 

  - 链接器
    - 附加依赖项 —— `glfw3.lib` （`opengl32.lib` 在 visual studio 2019 SDK 中已经存在）, `soil2-debug.lib` 
- 添加文件
  - 将`glad.c` 从 `.\depend\src` 目录移动到到项目源文件目录（`.\source\$(ProjectName)\`）下
- 各个目录解释

```
opengl
|---bin				可执行文件
|---depend			opengl环境
|	|---include
|	|	|---glad
|	|	|---GLFW
|	|	|---KHR
|	|	|---glm		opengl运算库
|	|	\---SOIL2	纹理导入库
|	\---lib			glfw库文件
|---shader			GLSL文件
|---source			项目文件
\---temp			临时文件
```