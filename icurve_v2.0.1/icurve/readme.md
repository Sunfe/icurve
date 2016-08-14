icurve
==

1. 版本   
   > qt4.7.3 + qwt6.1.3
   > ?
2. 功能
   > 对既定格式的数据进行绘图
   > ?
3. TO DO list
   - curve filter [done]
   - legend checkable [done]
   - 支持多曲线操作 [done]
   - curve finder  [done]
   - axse  range[done]
   - 点击curve的时候curve title,legend也要做相应的变化[done]
   - 鼠标放到curve上的做曲线信息提示。
   - 鼠标拖放文件打开功能
   - 支持多tab
   - filter支持关键字[done]
   - filter/find支持补全[done]
   - 增加曲线取点[done]
   - 信息提示，包括在文件中的位置，显示该命令在文件中对应的一行[done]
   - 查找支持均值、峰值最大最小，平均波动最大，最小
   - 支持部分xdsl参数的估算
   - 查找、filter的时候增加预览[done]
   - 曲线增加树形分组
   - 加入recent file[done]
   - 增加曲线最大，最小值指示标志，标志还携带curve title信息[done]   
   - 支持多文件[done]
   - 增加工具栏[done]
   - 增加快捷键[done]
   - 加入曲线调整至合适的尺度
   - 加入数据保存
   - 增加曲线条数的信息
   - 增加打开文件时的路径记忆功能[done]
   - debug版本和release版本[done]
   - lint检查
   - 增加refresh[done]
   - 界面美化
   - 增加save工具栏
   - 加入对不同命令提示符的支持，如rfc,fast[done]
   - 加入对getaln，getrmcbitalloc数据格式的支持[done]
   - 优化数据匹配模式，加快数据解析速度[done]
   - 加入多条件filter
   - 坐标轴能实时调整
   - 右键将delete变更给remove[v2.0.1][done]
   - delete/remove如果没有选中，加入提示[v2.0.1][done]
   - 大批量绘制曲线的时候给出进度条[done]
   - 进度条显示可以以10为单位，减少信号发送的次数[done]
   - 查找时，输入部分关键字如“psd”的时候没有效果
   - 当曲线remove的时候indicator还会有显示。[done]
   - 还存在curve name已经加粗，但实际没有选中的情况。复现：选中，remove,showall
   - filter后后退到上一个状态
   - 加入aln、gfast的数据格式
   - filter加入端口list
   - 数据格式的多样化，如：>rfc getsnr all >rfc getsnr 1:2 0 >rfc getsnr 1,2 0[done]
   - filter,show all ,select all的时候加入进度条和sleep[done]
   - toolbar图标设置为24x24[done]

1. bugs
   - 多重filter后，再curve show all,会出现越界 [已解决]
   - 打开大文件后再取消，再打开小文件会出现越界。[已解决，diaglog指针没有清0]
   - 右键的menu状态不能维持多条曲线。
   - 有可能出现弹出右键菜单，但是没有曲线选中的情况。
   - remove后左键点击，crash
