# MSM
使用$libigl$实现简单的弹簧质点模型。
使用半隐式欧拉和$verlet$进行质点位置更新。

#### 2021/2/2
  项目进度：初步实现弹簧质点模型。
  当前问题：线的粗细，模型迭代不匀速。

#### 2021/2/2-1

 粗细问题解决，迭代问题来自libigl的实时渲染问题，现在解决如何将每次迭代之后的属性导出，等模拟完成之后再渲染。