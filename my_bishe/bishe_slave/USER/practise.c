/*
	2021��1��6��11:39:45
	�˿ڸ���&�˿���ӳ��
*/
/****************************
			����
****************************/		
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLLE); // ʹ�ܶ˿�
RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); // ʹ�ܴ���

//USART1_TX PA.9 �����������
GPIO_InitTypeDef GPIO_InitStructure
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
GPIO_Init(GPIOA, &GPIO_InitStructure);

//USART1_RX PA.10 ��������
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
GPIO_Init(GPIOA, &GPIO_InitStructure);

/*
	�����ܽ᣺
		��ʹ�ø��ù��ܵ���ʱ������Ҫʹ�� 2 ��ʱ�ӣ�
		1��GPIOʱ��ʹ��
		2�����õ�����ʱ��ʹ��
*/

/***********************
		��ӳ��
***********************/
1��ʹ�� GPIOB ʱ�ӣ�
RCC_APB2PeriphClockCmd(GPIOB, ENABLE);
2��ʹ�ܴ��� 1 ʱ�ӣ�
RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
3��ʹ�� AFIO ʱ�ӣ�
RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
4��������ӳ�䣺
GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);

/*
	��ӳ���ܽ᣺
		��ӳ��ͬ��Ҫʹ�ܸ��ù��ܵ�ʱ�򽲽�� 2 ��ʱ���⣬��Ҫʹ�� AFIO ����ʱ�ӣ�Ȼ��
		Ҫ������ӳ�亯��
*/
