#include<iostream>
#include<sstream>
#include<vector>

using namespace std;

typedef struct Node * Node_Pointer;
typedef struct Header* Header_Pointer;
typedef struct Edge * Edge_Pointer;

struct Header{
	bool checked;//To check whether this header has been check for minimum_Distance
	int key;//Record the key value of the vertex
	Node_Pointer Next;//Pointer to the vertex that edge linked to
	Header_Pointer Next_Header;//Point to a next header when tree is formed
	Header_Pointer Previous_Header;//point to a previous header when tree is formed
};

struct Edge{
	int head;
	int tail;
	int distance;
};

struct Node{
	int key;//record the key value of the vertex
	Node_Pointer Next;
	bool Used;//record whether this edge has been used/picked.
	int distance;
};

const char Split_Char=' ';
vector <int> temp_string;//To record thestring after split
vector<Header_Pointer> Header_Node;
vector<Edge_Pointer> Edge_Choosen;
int no_Edge,Head_changed;//No of edge entered by user
Header_Pointer temp_Header;
Node_Pointer temp_Node;
Edge_Pointer temp_Edge;
int minimum_Distance;
int no_Edge_conform=0;

void string_Split(string);//split string entered
int check_Header(int i);//check the index of specific header
int Find_Minimum(Header_Pointer);// find the minimum distance of edge indicate on this header
void Eliminate_Repeated_Edge();
void setTrue(int,int);


int main (){
	cout<<"Please enter the number of edge"<<endl;
	cin>>no_Edge;
	cin.ignore();
	for(int i=0;i<no_Edge;i++){
		string temp;
		getline(cin,temp);
		string_Split(temp);
		for(int j=0;j<2;j++){
			unsigned int index=check_Header(temp_string[j]);
			if(index==Header_Node.size()){
				temp_Header=new Header;
				temp_Header->key=temp_string[j];
				temp_Header->Next=NULL;
				temp_Header->Next_Header=NULL;
				temp_Header->Previous_Header=NULL;
				Header_Node.push_back(temp_Header);
			}
			temp_Node=new Node;
			temp_Node->distance=temp_string[2];
			temp_Node->Used=false;
			if(j==0){
				temp_Node->key=temp_string[1];
			}
			else{
				temp_Node->key=temp_string[0];
			}
			temp_Node->Next=Header_Node.at(index)->Next;
			Header_Node.at(index)->Next=temp_Node;
		}
	}
	cout<<"Output:"<<endl;
	while(no_Edge_conform!=Header_Node.size()-1){
		for(unsigned int i=0;i<Header_Node.size();i++){
			Header_Node.at(i)->checked=false;
		}
		for (unsigned int i=0;i<Header_Node.size();i++){
			if(!Header_Node.at(i)->checked){
				temp_Edge=new Edge;
				temp_Edge->tail=Find_Minimum(Header_Node.at(i));
				temp_Edge->head=Head_changed;
				temp_Edge->distance=minimum_Distance;
				Edge_Choosen.push_back(temp_Edge);
			}
		}
		Eliminate_Repeated_Edge();
		for(unsigned int i=0;i<Edge_Choosen.size();i++){
			int head=check_Header(Edge_Choosen.at(i)->head);
			int tail=check_Header(Edge_Choosen.at(i)->tail);
			if(Header_Node.at(tail)->Previous_Header)
			{
				Header_Node.at(tail)->Next_Header=Header_Node.at(head);
				Header_Node.at(head)->Previous_Header=Header_Node.at(tail);
			}
			else
			{
			Header_Node.at(head)->Next_Header=Header_Node.at(tail);
			Header_Node.at(tail)->Previous_Header=Header_Node.at(head);
		}
			cout<<Edge_Choosen.at(i)->head<<" "<<Edge_Choosen.at(i)->tail<<" ";
			cout<<Edge_Choosen.at(i)->distance<<endl;
			setTrue(Edge_Choosen.at(i)->head,Edge_Choosen.at(i)->tail);
			setTrue(Edge_Choosen.at(i)->tail,Edge_Choosen.at(i)->head);
			no_Edge_conform++;
			if(no_Edge_conform==Header_Node.size()-1){
				break;
			}
		}
		Edge_Choosen.erase(Edge_Choosen.begin(),Edge_Choosen.end());
	}
	}


	void setTrue(int Head,int Tail){
		int index=check_Header(Head);
		temp_Node=Header_Node.at(index)->Next;
		while(temp_Node){
			if(temp_Node->key!=Tail){
				temp_Node=temp_Node->Next;
			}
			else {
				break;
			}
		}
		temp_Node->Used=true;
	}
	void Eliminate_Repeated_Edge(){
		for (unsigned int i=0;i<Edge_Choosen.size();i++){
			int head_compare=Edge_Choosen.at(i)->head;
			int tail_compare=Edge_Choosen.at(i)->tail;
			for (unsigned int j=0;j<Edge_Choosen.size();j++){
				if(j!=i){
					if((Edge_Choosen.at(j)->head==head_compare )||(Edge_Choosen.at(j)->head==tail_compare)){
						if((Edge_Choosen.at(j)->tail==head_compare )||(Edge_Choosen.at(j)->tail==tail_compare)){
							Edge_Choosen.erase(Edge_Choosen.begin()+j);
							j--;
					}
				}
			}
		}
	}
}

int Find_Minimum(Header_Pointer initial){
	while(initial->Previous_Header){
		initial=initial->Previous_Header;
	}
	Head_changed=initial->key;
	minimum_Distance=1000;
	int tail;
	temp_Node=initial->Next;
	do{
		initial->checked=true;
		while(temp_Node){
			if(temp_Node->distance<minimum_Distance && !temp_Node->Used){
				tail=temp_Node->key;
				Head_changed=initial->key;
				minimum_Distance=temp_Node->distance;
			}
			temp_Node=temp_Node->Next;
		}
		if(initial->Next_Header){
			initial=initial->Next_Header;
			temp_Node=initial->Next;
		}
}while(temp_Node);
	return tail;
}
void string_Split(string s){
	temp_string.erase(temp_string.begin(),temp_string.end());
	istringstream ss(s);
	string temp;
	while(getline(ss,temp,Split_Char)){
			temp_string.push_back(stoi(temp));
	}
}

int check_Header(int key){
	unsigned int length=Header_Node.size();
	for (unsigned int i=0;i<length;i++){
		if(Header_Node.at(i)->key==key){
			return i;
		}
	}
	return length;
}
