使用cd 和 dir 命令切换到所在目录


showhide.bat 输出所有hide节点的权重图 参数为hide节点数 默认网络名称为sunglasses.net

对应人脸识别网络示例：
showhide.bat 6


showout.bat 输出所有out节点的映射权重图 参数为out节点数 hide节点数 默认网络名称为sunglasses.net

对应人脸识别网络示例：
showout.bat 5 6


FaceTrain工程
在FaceTrain.h文件中，使用宏BPNN_TYPE切换Task
BPNN_TYPE 0 //对应Task1
BPNN_TYPE 1 //对应Task2