/*
	2021年1月6日11:39:45
	端口复用&端口重映射
*/
/****************************
			复用
****************************/		
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLLE); // 使能端口
RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); // 使能串口

//USART1_TX PA.9 复用推挽输出
GPIO_InitTypeDef GPIO_InitStructure
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出
GPIO_Init(GPIOA, &GPIO_InitStructure);

//USART1_RX PA.10 浮空输入
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
GPIO_Init(GPIOA, &GPIO_InitStructure);

/*
	复用总结：
		在使用复用功能的是时候，最少要使能 2 个时钟：
		1）GPIO时钟使能
		2）复用的外设时钟使能
*/

/***********************
		重映射
***********************/
1）使能 GPIOB 时钟：
RCC_APB2PeriphClockCmd(GPIOB, ENABLE);
2）使能串口 1 时钟：
RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
3）使能 AFIO 时钟：
RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
4）开启重映射：
GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);

/*
	重映射总结：
		重映射同样要使能复用功能的时候讲解的 2 个时钟外，还要使能 AFIO 功能时钟，然后
		要调用重映射函数
*/
