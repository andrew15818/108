int BFS_search(int startx, int starty, int endx, int endy)
{
	std::list<Node*> frontier;
	//preprocessing

	int index = get_index(startx, starty);
	Node* initial = &board[index];
	initial->parent = NULL;
	frontier.push_back(initial);
	
	while(!frontier.empty())
	{
		Node* current = frontier.front();
		
		//if(!is_valid(current->x, current->y)){ 
		//	continue;
		//}
		current->discovered = 1;
		//printf("checking: (%d, %d)\n", current->x, current->y);
		if(current->x == endx && current->y == endy){
			printf("Found Target.\n");
			print_path(current, startx, starty);
			return expanded;
		}
		expanded++;
		frontier.pop_front();
		Node* tmp = &board[get_index(current->x + 1, current->y + 2)];
		current->discovered = 1;

		for(int i=0; i< CHILD_NO; i++){
			int x = current->x, y = current->y;
			switch(i % CHILD_NO){
				case 0:
					x+=1;y+=2;
					break;
				case 1:
					x+=1;y-=2;
					break;
				case 2:
					x-=1;y+=2;
					break;
				case 3:
					x-=1;y-=2;
					break;
				case 4:
					x+=2;y+=1;
					break;
				case 5:
					x+=2;y-=1;
					break;
				case 6:
					x-=2;y+=1;
					break;
				case 7:
					x-=2;y-=1;
					break;
			}
			//add child point to frontier if valid
			if(is_valid(x, y)){
				if(!board[get_index(x, y)].discovered){
					frontier.push_back(&board[get_index(x, y)]);
					board[get_index(x,y)].parent = current;
				}
			}
		}
		
	}
	return 0;
}
