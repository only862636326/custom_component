
一些自用C库



2025/11/20 evn
  - 添加可通过idx快速触发事件

2025/12/01 uni_io
- 删除了component_uni_io模块中的调试板功能
- 移除了debug_drv全局变量及相关代码
- 删除了与调试功能相关的打印函数实现
- 更新了UniIO_Drv_Register函数，移除了DRV_ID_DEBUG的特殊处理
- 修复了UniIO_Drv_Get和UniIO_Drv_Open函数中的逻辑错误
- 更新了日志系统以适应debug_drv的删除

2025/12/02 uni_io
- 调整了read、write、read_async、write_async、read_call、write_call等函数的参数顺序，将dat和len的位置进行了交换
- 更新了Type_UniIO_PInfo_t结构体中dat和len的顺序
- 更新了null_fun函数的参数顺序
- 将uni_io中len和timeout参数的数据类型从int32_t改为uint32_t
- 将dat参数的数据类型从char*改为uint8_t*
- 填加uni_io快速定义 
- 注册时带返回值

2025/12/04 main 
- merge 

2025/12/06 FSM
- 添加优先级，每个状态机可设置一个优先级，默认0
- 添加HopeFsm_GetByName, 可根据名称获取状态机
- updata 只更新node结点，避免父节点、子节点都更新

2025/12/09 uni_io
- 改为UniIO_Drv_OPEN 改为UniIO_Drv_GetByName， 更符合实际
  
2025/12/23 main fsm 
- fsm val change to current_sta_id
- del p2 
- add define CALL_IF_NOT_NULL(func, param)
- test

2025/12/30 main fw 
- 修复fw中的定义错误
- 所有文件不在使用component_include.h, component_include.h仅为外部使用
- 添加component_config.h

2025/12/31 main uni_io
- uni_io async define 控制，减少变量
- movd config define to component_config.h
- HopeFsm_GetByName， 参数更改

2025/12/31 main top_fw
- 添加一些函数

2026/01/06 main fsm
- 添加fsm - BhangeByBame;
- rename hope_component_fsm to component_fsm