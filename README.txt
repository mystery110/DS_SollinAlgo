Variable
-Three different struct is declared to record different information .Since it is a undirected graph , for every vertex , there will has a coresponding 
 header and multiple node.Node record the head it is connected to or tail it is connected by .
 a)Header struct
   -)int key to record the key value of the vertex
   -)bool used to check whether this vertex or tree has been checked to find the minimum cost of edge
   -)Node Pointer to record the pointer point to the node that this vertex is connected to 
   -)Header_pointer Next Header: this pointer will point to a Header when a tree is forment . Let say if edge(1,2)is picked , header[1]->next_pointer will 
     points toward header[2] while header[2]->previous_pointer will points toward header[1].

  b)Edge struct 
   -)To record the information of an edge . The variable name clearly show what it is recording.

  c)Node struct
   -)similar to header struct but no Next_header & previous_Header
   -)bool used to check whether this edge has been used before(when this is set to true,it will just like delte this edge from consideration)

-)vector temp_strng to record the string entered by user after splitting it

-)vector<Header_Pointer> Header_Node & 
vector<Edge_Pointer> Edge_Choosen record the pointer to each header and edge that is choosen to be edge in minimum
  spanning tree

-)int no_edge to record number of edge entered by user.int no_Edge_conform will record the edge conform to be part of minimim spanning tree.


Function
-)void function string split will juz split the string entered by user and record the result in the vector temp_string.

-)Because vector<Header_Pointer> is used, the index of this vector does not represent the key value of the vertex. For instance , vertex with key value =1 is
 is not stored at Header_Node.at(1).Instead , it's index in the vector is unknown. Therefore,function check_Header is used to check the existence of the header
 in the vector and return it's index if it exist . If not , return the size of the vector Header_node;

-)Function Find_Minimum.this function required a header_pointer as argument. First , it will go up the header_node by the previous_Header in Header struct.After it 
  reach the top , it will the find the edge in this tree that has the minimum cost .When this header-linked-list terminate, it will move to the next header(just like
  tree).It will then return the tail/head of the edge found and set the int Head_change to the coresponding tail/head.While going through the header , it will set the 
  used boolen to true to indicate that this header-linked-list has been checked.

-)Function Eliminate_Repeated_Edge just eliminate the edge if same edge has been choose twice

-)Function SetTrue:After the edge has been conform , let say edge(1,2), this function find header with key in header struct taht is 1/2 and find the linked node with 
  it's key equal to 1/2. It will that set the Used boolen to be true so that the next time FindMinimum function is called,this edge will not be take into consideration.


Main Program
-)When the user start entering the edge , the main function will call Check_Header.If the correcponding header does not exist , it will create a new header for this 
  vertex.If it exist , then it will update the header by adding a new node to it. This part will be executed twice since two vertex has been involved.Initially , all 
  Next_Header and Previous_Header is set to NULL since every vertices is a tree.

-)while the No_edge_conform is less than the number of vertices -1(assuming minimum spanning tree exist), the while loop will keep finding edge
  
-)initially , it will set checked boolean in every header to false.For every header that it's checked is false , this header is passed to function FindMinimun to find 
  edge with minimum cost. The edge choosen will that push back to the vector Edge_Choosen.

-)after all the header is examine ,Eliminate_Repeated_edge will be called to remove the repeated edge in the vector Edge_Choosen.The edge left in the vector will be 
  the edge in the minimum spanning tree.

-)The function will start linking the header according to the head and tail recorded in the edge strcut .The edge is print out and set_true function will be called.

-)this process will be continue until no_of_vectices -1 edge is choosen.