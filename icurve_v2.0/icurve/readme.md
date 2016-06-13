icurve
=

1. 版本   
   > qt4.7.3 + qwt6.1.3
   > ​
2. 功能
   > 对既定格式的数据进行绘图
   > ​
3. TO DO list
   - curve filter [done]
   - legend checkable [done]
   - 支持多曲线操作 [done]
   - curve finder 
   - axse  range
   - 点击curve的时候curve title,legend也要做相应的变化
   - 鼠标放到curve上的做曲线信息提示。
   - 鼠标拖放文件打开功能
   - 支持多tab
   - filter支持关键字


1. bugs
   - 多重filter后，再curve show all,会出现越界 [已解决]
   - 打开大文件后再取消，再打开小文件会出现越界。[已解决，diaglog指针没有清0]
   - 右键的menu状态不能维持多条曲线。
   - 有可能出现弹出右键菜单，但是没有曲线选中的情况。
   - remove后左键点击，crash