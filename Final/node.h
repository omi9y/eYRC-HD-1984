/*
* Team Id :eYRC-HD#1984
* Author List : Omprakash Jha, Jitesh Gupta, Melwyn Saldanha, Crystal Cuthinho
* Filename: node.h (header file)
* Theme: Hazardous Waste Disposal	-----eYRC
* Functions: node0_0(int flag), node_m1_0(int flag), node_m2_0(int flag), node_0_1(int flag,int valid), node_m1_1(int flag,int valid), node_1_1(int flag),
  node_2_1(int flag), balanceBridge(int flag) 
* Global Variables: sortedFlag[3], index, a_flag, b_flag, c_flag
*/

int sortedFlag[3]= {0};				
int index = 0;
int a_flag=0, b_flag = 0, c_flag = 0;

/* We have divided each node of the flex as the co-ordinates of the XY plane with starting position node as(0,0).
   if we go left to this node than we will get node such as (-1,0), (-2,0) etc. Then in each node we made the sub functions by passing a flag value
   i.e. the different actuations the bot will do at those nodes.
*/

/*
* Function Name: node0_0(int flag)
* Input : flag
* Output : Multiple Outputs explained in the logic 
* Logic:  when flag value is 0 it will take the left turn and move forward.when flag value is 1 the bot will 
		  take the right turn and will move forward by black line following. when flag value is 2 the bot will take right turn.when flag value is 3 then the
		  bot will take right turn and will pick the uppermost block after balancing the bridge.when flag value is 5 then the bot will pick the middle block 
		  after placing the first block in isolated area. when flag value is 6 then the bot will pick the bottom most block after placing the second block in
		  isolated area.when flag value is 7 then the bot will pick the topmost block after balancing the bridge in city area. when flag value is 8 then the 
		  bot will take left turn and will follow the black line.   
* Example Call: node0_0(0);
*/
int node0_0(int flag)	
{	
	//when flag value is 0 it will take the left turn and move forward
	if (flag==0)					
	{
		velocity(180,180);
		backward_mm(20);
		left_degrees(88,0);//100/70
		fw_follow_black_line();
		//fw_follow_black_line();
		//fw_follow_black_line();
		
	}
	//when flag value is 1 the bot will take the right turn and will move forward by black line following
	else if (flag==1)				//turn right towards sorting zone
	{
		_delay_ms(100);
		velocity(180,180);
		forward_mm(50);
		right_degrees(88,0);
		backward_mm(40);
		fw_follow_black_line();
	}
	// when flag value is 2 the bot will take right turn
	else if (flag==2)
	{
		right_degrees(88,0);
	}
	//when flag value is 3 then the bot will take right turn and will pick the uppermost block after balancing the bridge
	else if (flag==3)
	{
		forward_mm(30);
		velocity(180,180);
		left_degrees(90,0);
		fw_follow_black_line();
		left_degrees(100,0);
		pick_block(90);
		right_degrees(88,0);
	}
	/*when flag value is 4 then the bot will take 180 turn and will pick the uppermost block.This flag will be called when the the bot will not have to 
	balance the bridge*/
	else if(flag == 4)
	{					
		servo_1(130);
		servo_2(120);
		_delay_ms(200);
		velocity(180,180);
		left_degrees(88,0);
		backward_mm(40);
		left_degrees(88,0);
		backward_mm(23);
		forward_mm(10);
		backward_mm(15);
		pick_block(107);
		forward_mm(15);
		backward_mm(120);
	}
	//when flag value is 5 then the bot will pick the middle block after placing the first block in isolated area
	else if(flag==5)
	{	
		forward_mm(50);
		pick_block(96);
		backward_mm(60);
		right_degrees(88,0);
		fw_follow_black_line();
	}
	//when flag value is 6 then the bot will pick the bottom most block after placing the second block in isolated area
	else if(flag==6)
	{	
		servo_2(120);
		forward_mm(70);
		pick_block(85);
		backward_mm(80);
		right_degrees(88,0);
		backward_mm(50);
		right_degrees(88,0);
		fw_follow_black_line();
	}
	//when flag value is 7 then the bot will pick the topmost block after balancing the bridge in city area
	else if(flag==7)
	{	
		forward_mm(50);
		pick_block(110);
		backward_mm(60);
		right_degrees(88,0);
		fw_follow_black_line();
	}
	//when flag value is 8 then the bot will take left turn and will follow the black line
	if (flag==8)	
	{
		velocity(180,180);
		forward_mm(20);
		left_degrees(88,0);
		_delay_ms(50);
		fw_follow_black_line();
	}
}

/*
* Function Name: node_m1_0()
* Input : flag
* Output : Multiple Outputs explained in the logic
* Logic:when flag value is 0 will rotate right while coming from node (1,0) carrying weight block and will put the weight block in the weight container.
		when flag value is 1 it will rotate left while coming from node (-2,0) carrying weight block and will put the weight block in the weight container.
		when flag value is 2 it will make the bot to move forward to 19.5 cm. this is hard coded because for short distance the black line following with
		pid is bit difficult as the bot will take some time to settle down because of the nature of the pid. when flag value is 3 it will follow the straight line.
		when flag value is 4 the bot will move 19cm forward used while balancing the bridge.
* Example Call: node_m1_0(1);
*/
int node_m1_0(int flag)
{
	//when flag value is 0 it will rotate right while coming from node (1,0) carrying weight block and will put the weight block in the weight container 
	if(flag==0)				//turn right and drop weight block
	{
		velocity(180,180);
		right_degrees(90,0);
		backward_mm(20);
		drop_weight();
		backward_mm(40);
		right_degrees(88,0);
		fw_follow_black_line();
	}
	//when flag value is 1 it will rotate left while coming from node (-2,0) carrying weight block and will put the weight block in the weight container
	if(flag==1)
	{
		velocity(180,180);
		left_degrees(93,1);
		backward_mm(20);
		drop_weight();
		backward_mm(40);
		right_degrees(88,0);
		fw_follow_black_line();
	}
	/*when flag value is 2 it will make the bot to move forward to 19.5 cm. this is hard coded because for short distance the black line following with pid 
	is bit difficult as the bot will take some time to settle down because of the nature of the pid */ 
	if(flag==2)					//go straight
	{
		velocity(200,200);	//150,200
		//forward_mm(195);
		fw_follow_black_line();
	}
	//when flag value is 3 it will follow the straight line
	if(flag==3)
	{   
		fw_follow_black_line();
		stop();
	}
	//when flag value is 4 the bot will move 19cm forward used while balancing the bridge
	if(flag==4)					//go straight
	{
		velocity(190,180);
		forward_mm(190);
	}
}

/*
* Function Name: node_m2_0()
* Input : flag
* Output : Multiple Outputs explained in the logic
* Logic:when flag value is 0 it will pick the block from the sorting zone and will start to move the isolated area.when flag is 1 it will place
  the block in sorting zone and it will detect the color and will store the result in variable sortedFlag[]  
* Example Call: node_m2_0(1)
*/
int node_m2_0(int flag)
{
	//when flag value is 0 it will pick the block from the sorting zone and will start to move the isolated area
	if (flag == 0)
	{							//pick weight block
		pick_block(90);
		right_degrees(185,1);
		backward_mm(30);
		fw_follow_black_line();
	} 
	//when flag is 1 it will place the block in sorting zone and it will detect the color and will store the result in variable sortedFlag[]
	else if (flag == 1)
	{											//place block in sorting zone 
		velocity(180,180);
		right_degrees(88,0);
		backward_mm(25);
		place_to_sort();
		forward_mm(150);
		_delay_ms(500);
		sortedFlag[index] = detect_color();
		index++;
		print_color(sortedFlag[index - 1]);
		velocity(180,180);		//180,165
		backward_mm(140);
		pick_at_sort();
		backward_mm(50);
		right_degrees(90,0);
		velocity(190,220);
		backward_mm(50);
		fw_follow_black_line();
		velocity(255,255);
	}	
}

/*
* Function Name: node_0_1()
* Input : flag,valid
* Output : Multiple function explained in logic
* Logic: when flag is 0 and valid is 1 then this whole flag==0 loop will be executed. Here it will detect the flag color,place if color matches. The valid
		part only works in the first run since we are detecting all the flags in first run and it is controlled by passing different parameters though
		implementation file. when flag is 1 it will take left turn and will follow the black line.when flag is 2 it will take right turn and will follow the
		black line 
* Example Call: node_0_1(0,1);
*/
int node_0_1(int flag,int valid)
{
	/*when flag is 0 and valid is 1 then this whole flag==0 loop will be executed. Here it will detect the flag color,place if color matches. The valid
	part only works in the first run since we are detecting all the flags in first run and it is controlled by passing different parameters though
	implementation file*/
	if (flag==0)				//detect color at B-flag and place block if color matches 
	{
		if(valid){
		forward_mm(190);
	 	rotate_at_flag();
		b_flag=detect_color();
		print_color(b_flag);
		backward_mm(50);
		stop();
		_delay_ms(500);
		left_degrees(58,1);//60/62
		stop();
		_delay_ms(500);
		velocity(255,195);
		backward_mm(150);//220/160
	
		stop();
		_delay_ms(500);
		soft_right_2();
		_delay_ms(630);
		velocity(180,180);
		stop();
		_delay_ms(2000);
		}		
		if (b_flag==sortedFlag[index-1])		//place block and go over bridge
		{
			buzzer_on();
			_delay_ms(200);
			buzzer_off();
			place_block();
			
		}
		
	}
	//when flag is 1 it will take left turn and will follow the black line
	if (flag==1)			//turn left 
	{
		//left();
		//_delay_ms(1);
		backward_mm(20);
		left_degrees(88,0);
		fw_follow_black_line();
	}
	//when flag is 2 it will take right turn and will follow the black line
	if (flag==2)			//turn right 
	{
		right_degrees(67,1);
		fw_follow_black_line();
	}
}

/*
* Function Name: node_m1_1()
* Input : flag,valid
* Output : none
* Logic: when flag is 0 and valid is 1 then this whole flag==0 loop will be executed. Here it will detect the flag color,place if color matches. The valid
		part only works in the first run since we are detecting all the flags in first run and it is controlled by passing different parameters though
		implementation file. when flag is 1 it is used to take right angle and to follow the black line.
* Example Call: node_m1_1(0,1)
*/
void node_m1_1(int flag,int valid) 
{
	/*when flag is 0 and valid is 1 then this whole flag==0 loop will be executed. Here it will detect the flag color,place if color matches. The valid 
	part only works in the first run since we are detecting all the flags in first run and it is controlled by passing different parameters though
	 implementation file*/ 
	if (flag == 0) 
	{								
		right_degrees(93,0);
	
		if(valid)		//the bot will move from B flag to C flag
		{
			forward_mm(115);
			rotate_at_flag();
			backward_mm(10);
			c_flag = detect_color();
			print_color(c_flag);
			backward_mm(50);
			stop();
			_delay_ms(500);
			left_degrees(60,1);
			stop();
			_delay_ms(500);
			velocity(255,195);
			backward_mm(150);//170
	
			stop();
			_delay_ms(500);
			soft_right_2();
			_delay_ms(550);
			velocity(180,180);
			stop();
			_delay_ms(2000);
		}	
		if (c_flag == sortedFlag[index-1])		//if sorted flag is same as the waste then the waste block then the waste block is placed  
		{
			forward_mm(15);
			place_block();
			backward_mm(35);
			velocity(150,150);
			right_degrees(100,0);
			fw_follow_black_line();
			node_0_1(2,0);
		
		}
	else
	{										//if above condition is not satisfied than waste block is taken towards A flag and will be placed over there 
		backward_mm(35);//20
		right_degrees(100,0);
		velocity(150,150);
		fw_follow_black_line();
		fw_follow_black_line();
		fw_follow_black_line();
		left_degrees(88,0);
		backward_mm(20);
		place_block();
		left_degrees(88,0);
		fw_follow_black_line();
		fw_follow_black_line();
		left_degrees(95,1);
	}
} 
//when flag is 1 it is used to take right angle and to follow the black line 
else if (flag == 1)
	{									//pick weight block
		right_degrees(200,0);
		fw_follow_black_line();
	}
}

/*
* Function Name: node_1_1()
* Input : flag
* Output : Actuations done at node(1,1) placing the weight block in the weight container in IA
* Logic: when flag is 0 it will turn right carrying the weight block from the node(-1,1) and will put the weight block in weight block in weight container.
		 when flag is 1 it will turn left carrying the weight block from the node(2,1) and will put the weight block in weight block in weight container.
		 when flag is 2 it will follow the black line.
* Example Call: node_1_1(0);
*/
int node_1_1(int flag)
{
	//when flag is 0 it will turn right carrying the weight block from the node(-1,1) and will put the weight block in weight block in weight container
	if(flag==0)				//turn right and drop weight
	{
		velocity(180,180);
		right_degrees(100,0);
		backward_mm(50);
		drop_weight();
		left_degrees(100,0);
		fw_follow_black_line();
		stop();
	}
	//when flag is 1 it will turn left carrying the weight block from the node(2,1) and will put the weight block in weight block in weight container
	if(flag==1)
	{
		velocity(180,180);
		left_degrees(100,0);
		backward_mm(50);
		drop_weight();
		right_degrees(100,0);
		stop();
	}
	//when flag is 2 it will follow the black line
	if(flag==2)					//go straight
	{
		fw_follow_black_line();
	}
}

/*
* Function Name: node_2_1()
* Input : flag
* Output : actuations explained in the logic
* Logic: when flag is 0 it will it will place the sorted weight block at node (2,1) 
* Example Call: node_2_1(1);
*/
void node_2_1(int flag)
{
	//when flag is 0 it will it will place the sorted weight block at node (2,1) 
	if(flag==0)						//turn left and place
	{
		velocity(180,180);
		left_degrees(128,0);
		backward_mm(50);
		place_block();
		velocity(180,225);
	}
}

/*
* Function Name: balanceBridge()
* Input : flag
* Output : These functions are used to balance the bridge in CA and IA
* Logic: when flag value is 0 it will take one weight block from node(-2,0) and will balance the bridge in CA during the first run.when flag
         value is 1 will take two weight blocks from node(2,1) and will balance the bridge in IA. hen flag value is 2 will take two weight
		 blocks from node(1,0) and will balance the bridge in CA. 	//when flag value is 3 will take two weight blocks from node(-1,1) and 
		 will balance the bridge in IA and again it will carry one weight from IA to the CA since we have one less weight block in CA and it
		 will put that in weight container of CA.when flag value is 4 will take two weight blocks from node(-2,0) and will balance the bridge in CA 
* Example Call: balanceBridge(0);
*/
void balanceBridge(int flag)
{
	//when flag value is 0 it will take one weight block from node(-2,0) and will balance the bridge in CA during the first run
	if (flag==0)
	{
		servo_1(130);		//Initializes the arm
		servo_2(120);
		_delay_ms(1000);
		node0_0(8);
		node_m1_0(4);
		backward_mm(35);
		node_m2_0(0);
		node_m1_0(1);
		node0_0(2);
		backward_mm(60);
		fw_follow_black_line();
	}
	
	//when flag value is 1 will take two weight blocks from node(2,1) and will balance the bridge in IA
	if (flag==1)
	{
		servo_1(150);
		servo_2(120);
		_delay_ms(1000);
		forward_mm(30);
		velocity(180,180);
		left_degrees(90,0);
		backward_mm(20);
		
		
		fw_follow_black_line();
		fw_follow_black_line();
		backward_mm(30);
		pick_block(88);
		velocity(180,180);
		forward_mm(30);
		right_degrees(190,0);
		velocity(190,177);
		backward_mm(30);
		fw_follow_black_line();
		left_degrees(90,0);
		backward_mm(20);
		drop_weight();
		backward_mm(25);
		
		//starts again to put second weight block 
		left_degrees(88,0);
		fw_follow_black_line();
		pick_block(82);
		right_degrees(180,0);
		fw_follow_black_line();
		left_degrees(88,0);
		backward_mm(20);
		drop_weight();
		backward_mm(20);
		
		//goes to node(0,1)
		right_degrees(88,0);
		fw_follow_black_line();
		left_degrees(67,1);
		fw_follow_black_line();	
	}
	//when flag value is 2 will take two weight blocks from node(1,0) and will balance the bridge in CA
	if (flag==2)
	{
		servo_1(150);
		_delay_ms(1000);
		node0_0(3);
		fw_follow_black_line();
		fw_follow_black_line();
		node_m1_0(0);				//drops first weight in weight container
		 
		fw_follow_black_line();
		left_degrees(100,0);
		pick_block(82);
		right_degrees(88,0);
		fw_follow_black_line();
		fw_follow_black_line();
		node_m1_0(0);				//drops second weight in weight container 
		
		//Goes to initial position i.e. node(0,0)
		right_degrees(88,1);
	}
	//when flag value is 3 will take two weight blocks from node(-1,1) and will balance the bridge in IA and again it will carry one weight from IA to the
	// CA since we have one less weight block in CA and it will put that in weight container of CA
	if (flag==3)
	{
		servo_1(150);
		servo_2(120);
		_delay_ms(1000);
		right_degrees(88,0);
		backward_mm(30);
		fw_follow_black_line();
		backward_mm(20);
		pick_block(90);
		forward_mm(30);
		left_degrees(180,0);
		fw_follow_black_line();
		fw_follow_black_line();
		right_degrees(88,0);
		drop_weight();				//drops first weight in weight block container
		
		//returns back to pick second weight block
		right_degrees(88,0);
		fw_follow_black_line();
		fw_follow_black_line();
		pick_block(82);
		left_degrees(176,0);
		fw_follow_black_line();
		fw_follow_black_line();
		right_degrees(88,0);
		drop_weight();				//drops second weight in weight block container
		right_degrees(88,0);
		fw_follow_black_line();
		fw_follow_black_line();
		left_degrees(88,0);
		pick_block(90);				//pick one more weight block and carries that weight block to CA
		left_degrees(88,0);
		fw_follow_black_line();
		right_degrees(88,0);
	}
	//when flag value is 4 will take two weight blocks from node(-2,0) and will balance the bridge in CA
	if (flag==4)
	{
		right_degrees(88,0);
		fw_follow_black_line();
		velocity(180,180);
		right_degrees(90,0);
		backward_mm(20);
		drop_weight();			//puts the carried weight block from IA to CA
		left_degrees(88,0);
		fw_follow_black_line();
		pick_block(82);			//picks another weight block from node(-2,1) and drops that in weight container in CA
		left_degrees(176,0);
		fw_follow_black_line();
		node_m1_0(1);
		right_degrees(88,0);		//reaches to the starting position that node(0,0) from where it will take the third waste block
	}
}