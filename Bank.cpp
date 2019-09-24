#include<iostream.h>
#include<string.h>
int ClockTime;
using namespace std;
class Bank;
template <typename T>
class queue;
void PutTaskName(string &,int &,int);
void PutPriority(string &,int);
template <typename T>
void PutTime(queue <T>&,int ,int);
template <typename T>
void Order(queue <T>&);
template <typename T>
int size(queue <T>);
template <typename T>
void notyetserved(queue <T>,queue <T>);
void convertoHours(int );
enum errorcode{success,underflow,overflow,notfound};
template<typename T>
void AddRandomly(Bank temp[],int n,queue<T>,queue<T>,queue<T>);
template <typename T>
void Rearrange(queue <T>&);
bool compare(string , string);
template <typename T>
bool Right(queue <T>,int);
template <typename T>
void WaitTimeForTasks(queue <T>,queue <T>,queue<T>);
template <typename T>
void TimeToFinish(queue <T>);
template <typename T>
void NotToday(queue <T>);
template <typename T>
void ServedTasks(queue <T>);
template <typename T>
void CarryOver(queue <T>&,queue <T>&);
template <typename T>
bool CheckID(queue <T>,queue<T>,queue<T>,int);
template <typename T>
void CarryOn(queue <T>&,queue<T>&);
template <class T>
struct Node{
	T data;
	Node <T>*Next;
	Node(){
		Next=0;
	}
	Node(T item){
		data = item;
		Next=0;
	}
};
template <class T>
class queue{
	Node<T>*Front ,*Rear;
	int count;
	public:
	queue(){
		Front=Rear=0;
		count=0;
	}
	~queue(){
		while(!empty())
		serve();
	}
	void operator=(queue&);
	queue(queue&);
	bool empty(){
		return(Front==0);
	}
	errorcode Append(T item){
		Node <T>*temp=new Node<T>(item);
		if(temp==0)
		return overflow;
		if(empty())
		Front=Rear=temp;
		else{
			Rear->Next=temp;
			Rear=Rear->Next;
		}
		count++;
		return success;
		
	}
	errorcode serve(){
		if(empty())
		return underflow;
		Node <T>*temp=Front;
		Front=Front->Next;
		if(Front==0)
		Rear=0;
		delete temp;
		count--;
		return success;
	}
	errorcode Retrieve(T &item){
		if(Rear==0)
		return underflow;
		item=Front->data;
		return success;
	}
	errorcode Back(T &item){
		if(empty())
		return underflow;
		item=Rear->data;
		return success;
	}
};
template <typename T>
void queue<T>::operator=(queue &T1){
	while(!empty())
	serve();
	if(T1.Front!=0){
		Node <T>*newfront=0;
		Node <T>*temp=T1.Front;
		newfront=new Node<T>(temp->data);
		Node <T>*temp2=newfront;
		temp=temp->Next;
		while(!temp.empty){
			temp2->Next=new Node<T>(temp->data);
			temp=temp->Next;
			temp2=temp2->Next;
		}
		Front=newfront;
		Rear=temp2;
		
	}
	
}
template <typename T>
queue<T>::queue(queue &T1){
	Node <T>*newlist;
	Node <T>*original=T1.Front;
	if(T1.Front==0)
	Front=0;
	else{
		Front=newlist=new Node<T>(original->data);
		original=original->Next;
		while(original!=0){
			newlist->Next=new Node<T>(original->data);
			newlist=newlist->Next;
			original=original->Next;
		}
		Rear=newlist;
	}
	
}
class Bank{
	int TaskID;
	string Taskname;
	int ArrivalTime;
	int WaitTime;
	int StartTime;
	int PeriodTime;
	string Priority;
	public:
	Bank();
	Bank(int,string,int,int,int,string);
	friend istream & operator>>(istream &,Bank &);
	void SetID(int );
	void SetName(string );
	void SetArrivalTime(int );
	void SetWaitTime(int );
	void SetStartTime(int );
	void SetPeriod(int );
	void SetPriority(string );
	int GetID();
	string GetName();
	int GetArrivalTime();
	int GetWaiTtime();
	int GetStartTime();
	int GetPeriodTime();
	string GetPriority();
	
	
};
void Bank::SetID(int TaskID){
	this->TaskID=TaskID;
}
void Bank::SetName(string Taskname){
	this->Taskname=Taskname;
}
void Bank::SetArrivalTime(int	 ArrivalTime){
	this->ArrivalTime=ArrivalTime;
}
void Bank::SetWaitTime(int WaitTime){
	this->WaitTime=WaitTime;
}
void Bank::SetStartTime(int StartTime){
	this->StartTime=StartTime;
}
void Bank::SetPeriod(int PeriodTime){
	this->PeriodTime=PeriodTime;
}
void Bank::SetPriority(string Priority){
	this->Priority=Priority;
}
int Bank::GetID(){
	return TaskID;
}
string Bank::GetName(){
	return Taskname;
}
int Bank::GetArrivalTime(){
	return ArrivalTime;
}
int Bank::GetWaiTtime(){
	return WaitTime;
}
int Bank::GetStartTime(){
	return StartTime;
}
int Bank::GetPeriodTime(){
	return PeriodTime;
}
string Bank::GetPriority(){
	return Priority;
}
Bank::Bank(){
		TaskID=0;
		Taskname='\0';
		ArrivalTime=0;
		WaitTime=0;
		StartTime=0;
		PeriodTime=0;
		Priority='\0';
}
Bank::Bank(int TaskID,string Taskname,int WaitTime,int StartTime,int PeriodTime, string Priority){
		this->TaskID=TaskID;
		this->Taskname=Taskname;
		this->WaitTime=WaitTime;
		this->StartTime=StartTime;
		this->PeriodTime=PeriodTime;
		this->Priority=Priority;
}
istream & operator>>(istream &in,Bank &customer){
	int choice;
	cout<<"Choice which Task you will have to do:\n";
	cout<<"1- Credit.\n2- Debit.\n3- Query.\n4- Open an account.\n5- Close an account.\n";
	cin>>choice;
	while(choice<1 || choice>5){
		cout<<"we don't have this Task enter another ID please:\n";
		cin>>choice;
	}
	PutTaskName(customer.Taskname,customer.PeriodTime,choice);
	cout<<"Let me know when you come,Enter The(Arrival Time):\n";
	int x,i=false;
	while(i==false){
		cout<<"Enter the hour: ";
		in>>x;
		while(x>13 || x<8){
		cout<<"Wrong hour,Please enter another hour: ";
		in>>x;
	}
	customer.ArrivalTime=x*60;
	cout<<"Enter the minutes: ";
	in>>x;
	while(x>60 || x<0){
		cout<<"Wrong minutes, Please enter another minutes: ";
		in>>x;
	}
		customer.ArrivalTime+=x;
	if(customer.ArrivalTime<ClockTime || customer.ArrivalTime>=14*60){
		cout<<"The Time must be between ";
		convertoHours(ClockTime);
		cout<<"and ";
		convertoHours(14*60-1);
		i=false;
	}
	else
	i=true;
	}
	cout<<"\nHow is your Task important(Your Priority):\n";
	cout<<"1- Normal Task.\n2- Important Task.\n3- VIP Task.\n";
	cin>>choice;
	while(choice>3 || choice<1){
			cout<<"Wrong number,enter another one: \n";
			cin>>choice;
		}
	PutPriority(customer.Priority,choice);
}

main(){
	cout<<"Good morning Bank of Jerusalem at your service.\n";
	ClockTime=8*60;
	cout<<"clock Time: ";
     convertoHours(ClockTime);
     cout<<endl;
	queue <Bank>Jerusalem;
	queue <Bank>Done;
	queue <Bank>Cannot;
	int choice;
	int arbiter=0;
	cout<<"Choice 1 to add an Task. \n";
	cout<<"Choice 2 to add an n Task randomly.\n";
	cout<<"Choice 3 to Rearrange the bank by the Priority.\n";
	cout<<"Choice 4 to finish the right Task.\n";
	cout<<"Choice 5 to know the information about a Task.\n";
	cout<<"Choice 6 to know the Total wait time for all Tasks.\n";
	cout<<"Choice 7 to know the Time needed to finish all tasks.\n";
	cout<<"Choice 8 to know who many Tasks can't complete and done today.\n";
	cout<<"Choice 9 to know The information of a served task.\n";
	cout<<"Choice 10 to know the information of all tasks not yet served.\n";
	cout<<"Press 11 to stop the program.\n";
	cin>>choice;
	while(choice!=11){
		switch(choice){
			case 1:{
				if(ClockTime>=14*60)
				cout<<"The Bank is closed, see you tomorrow.\n";
				else{
					Bank b1;
				int x;
				cout<<"Enter The ID: ";
				cin>>x;
				while(x<1 || CheckID(Jerusalem,Done,Cannot,x)==false){
					if(x<1)
					cout<<"This ID cannot be used, enter another one.\n";
					else
					cout<<"This ID is already used today, choose another one.\n";
					cin>>x;
				}
				b1.SetID(x);
				cin>>b1;
				cout<<"***************\n";
				Jerusalem.Append(b1);
				Order(Jerusalem);
				PutTime(Jerusalem,0,0);
				cout<<"The Task hase be added.\n";
				Jerusalem.Back(b1);
				CarryOver(Jerusalem,Cannot);
				if(b1.GetStartTime()==ClockTime)
				cout<<"The Employee will deal with you right now.\n";
				else{
				cout<<b1.GetWaiTtime()<<endl;
				cout<<"You have to wait for: "<<b1.GetWaiTtime()<<endl;
				cout<<"you will start at: ";
				convertoHours(b1.GetStartTime());
				}
				cout<<"Your Task takes time: ";
				convertoHours(b1.GetPeriodTime());
				}
				cout<<"***************\n\n";
				break;
			}
			case 2:{
				if(ClockTime>=14*60)
				cout<<"The Bank is closed, see you tomorrow.\n";
				else{
					cout<<"Enter who many Task you want to enter.\n";
				    int n,x,z;
				    cin>>n;
				    Bank b2[n],b3,b4;
				    if(Jerusalem.empty())
				    z=0;
				    else
				    z=1;
    				if(Jerusalem.Back(b3)==success)
				    x=b3.GetStartTime()+b3.GetPeriodTime();
				    else
				    if(Done.Back(b3)==success)
				    x=b3.GetStartTime()+b3.GetPeriodTime();
				    AddRandomly(b2,n,Jerusalem,Done,Cannot);
				    for(int i=0;i<n;i++)
				    Jerusalem.Append(b2[i]);
			     	Order(Jerusalem);
			     	if(arbiter==0)
			    	PutTime(Jerusalem,arbiter,0);
			    	else{
			    		Jerusalem.Retrieve(b4);
			    		if(z==0){
	    				if(b4.GetArrivalTime()>=x)
			    	     PutTime(Jerusalem,arbiter,0);
			    	     else
   	                     PutTime(Jerusalem,arbiter,x-b4.GetArrivalTime());
		    			}
		    			else
		    			PutTime(Jerusalem,arbiter,b4.GetWaiTtime());
		    			
	    			}
			    	CarryOver(Jerusalem,Cannot);
			    	arbiter=1;
			    	cout<<"clock Time: ";
			    	convertoHours(ClockTime);
				}
				cout<<"***************\n\n";
				break;
			}
			case 3:{
				if(Cannot.empty() && Jerusalem.empty())
				cout<<"There is no Tasks yet.\n";
				else
				if(ClockTime>=14*60)
				cout<<"The Bank is closed, see you tomorrow.\n";
				else{
					Bank b;
				    Rearrange(Jerusalem);
			     	Order(Jerusalem);
			     	Jerusalem.Retrieve(b);
			    	PutTime(Jerusalem,1,b.GetWaiTtime());
			    	Rearrange(Cannot);
			    	Order(Cannot);
			    	if(Jerusalem.Back(b)==success)
			     	PutTime(Cannot,1,b.GetWaiTtime());
    				else{
				      	if(Done.Back(b)==success)
				     	PutTime(Cannot,1,b.GetWaiTtime());
				     	else
				     	PutTime(Cannot,1,0);
				}
				CarryOn(Jerusalem,Cannot);
				CarryOver(Jerusalem,Cannot);
				cout<<"Important Tasks and VIP Tasks has been shifited Forward.\n";
				cout<<"3 minutes for Important Tasks.\n";
				cout<<"5 minutes for VIP Tasks.\n";
				}
				convertoHours(ClockTime);
				cout<<"***************\n\n";
				break;
			}
			case 4:{
				Bank temp,temp1;
				if(Jerusalem.Retrieve(temp1)==success){
				Done.Append(temp1);
				Jerusalem.serve();
				cout<<"The Task that has the ID ";
				cout<<temp1.GetID()<<" has been finished.\n";
				cout<<"The Task has finished at: ";
				convertoHours(temp1.GetStartTime()+temp1.GetPeriodTime());
				if(Jerusalem.Retrieve(temp)==success)
				ClockTime=temp.GetStartTime();
				else
					if(Done.Back(temp)==success)
					ClockTime=temp.GetStartTime()+temp.GetPeriodTime();
				}
				else
				cout<<"The Bank is empty.\n";
				cout<<"The clock is: ";
				convertoHours(ClockTime);
				cout<<"***************\n\n";
				break;
			}
			case 5:{
				if(Jerusalem.empty() && Cannot.empty() && Done.empty())
				cout<<"There is no Tasks yet.\n";
				else{
					int x;
	               cout<<"Enter the ID that you want to see the information of it: ";
                  cin>>x;
                  int z=Right(Jerusalem,x);
                  if(z==false)
				  z=Right(Done,x);
				  if(z==false)
				  z=Right(Cannot,x);
				  while(z!=true){
				  	cout<<"This ID is not exist Enter another ID: ";
				  	cin>>x;
					  z=Right(Jerusalem,x);
  					if(z==false)
					  	z=Right(Done,x);
  					if(z==false)
  					z=Right(Cannot,x);
  				}
  				z=false;
				}
				cout<<"***************\n\n";
				break;
			}
			case 6:{
				WaitTimeForTasks(Jerusalem,Done,Cannot);
				cout<<"***************\n\n";
				break;
			}
			case 7:{
			     TimeToFinish(Jerusalem);
			     cout<<"***************\n\n";
				break;
			}
			case 8:{
				NotToday(Cannot);
				cout<<"***************\n\n";
				break;
			}
			case 9:{
				ServedTasks(Done);
				cout<<"***************\n\n";
				break;
			}
			case 10:{
				notyetserved(Jerusalem,Cannot);
				cout<<"***************\n\n";
				break;
			}
		}
		cout<<"Choice 1 to add an Task. \n";
	    cout<<"Choice 2 to add an n Task randomly.\n";
	    cout<<"Choice 3 to Rearrange the bank by the Priority.\n";
	    cout<<"Choice 4 to finish the right Task.\n";
	    cout<<"Choice 5 to know the information about a Task.\n";
        cout<<"Choice 6 to know the Total wait time for all Tasks.\n";
        cout<<"Choice 7 to know the Time needed to finish all tasks.\n";
	    cout<<"Choice 8 to know who many Tasks can't complete and done today.\n";
        cout<<"Choice 9 to know The information of a served task.\n";
     	cout<<"Choice 10 to know the information of all tasks not yet served.\n";
        cout<<"Press 11 to stop the program.\n";
     	cin>>choice;
	}
	cout<<"See you tomorrow\n\n";
	
	
}
void PutTaskName(string &our,int &PeriodTime,int choice	){
	switch(choice){
	case 1:{
		our="Credit";
		cout<<"you have chosen Credit, this Task will take 10 minutes to be processed:\n";
		PeriodTime=10;
		break;
	}
	case 2:{
		our="Debit";
		cout<<"you have chosen Debit, this Task will take 15 minutes to be processed:\n";
		PeriodTime=15;
		break;
	}
	case 3:{
		our="Query";
		cout<<"you have chosen Query, this Task will take 20 minutes to be processed:\n";
		PeriodTime=20;
		break;
	}
	case 4:{
		our="Open an account";
		cout<<"you have chosen to Open an account, this Task will take 45 minutes to be processed:\n";
		PeriodTime=45;
		break;
	}
	case 5:{
		our="Close an account";
		cout<<"you have chosen to Close an account, this Task will take 60 minutes to be processed:\n";
		PeriodTime=60;
		break;
	}
	cout<<endl;
	}
}
void PutPriority(string &our,int choice){
	switch(choice){
		case 1:{
			cout<<"Your have no Priority(Normal Task).\n\n";
			our="Normal Task";
			break;
		}
		case 2:{
			cout<<"Your Priority is(Importnat Task).\n\n";
			our="Important Task";
			break;
		}
		case 3:{
			cout<<"Your Priority is (VIP Task).\n\n";
			our="VIP Task";
			
		}
		
	}
	
}
template <typename T>
void PutTime(queue <T>&jer,int z,int lasttime){
	Bank temp;
	int x=count(jer);
	queue <T>temp2;
	while(!jer.empty()){
		jer.Retrieve(temp);
		temp2.Append(temp);
		jer.serve();
	}
	
		Bank temp3[x];
		for(int i=0;!temp2.empty();i++){
			temp2.Retrieve(temp3[i]);
			temp2.serve();
		}
		for(int i=0;i<x;i++){
			if(i==0){
				if(z==0){
					ClockTime=temp3[i].GetArrivalTime();
					temp3[i].SetWaitTime(0);
					temp3[i].SetStartTime(temp3[i].GetArrivalTime());
				}
				else{
				temp3[i].SetWaitTime(lasttime);
				temp3[i].SetStartTime(temp3[i].GetArrivalTime()+temp3[i].GetWaiTtime());
				}
			}
			else{
				if(temp3[i-1].GetPeriodTime()+temp3[i-1].GetStartTime()<=temp3[i].GetArrivalTime()){
					temp3[i].SetStartTime(temp3[i].GetArrivalTime());
					temp3[i].SetWaitTime(0);
				}
				else{
					temp3[i].SetWaitTime((temp3[i-1].GetStartTime()+temp3[i-1].GetPeriodTime())-temp3[i].GetArrivalTime());
					temp3[i].SetStartTime(temp3[i].GetArrivalTime()+temp3[i].GetWaiTtime());
				}

			}
		}
		for(int i=0;i<x;i++)
		jer.Append(temp3[i]);
		
	
	
}
template <typename T>
int count(queue <T>q){
	int c=0;
	while(!q.empty()){
		q.serve();
		c++;
	}
	return c;
}
template <typename T>
void notyetserved(queue <T>out,queue<T>cannot){
	Bank temp;
	int c=0;
	while(!out.empty()){
		out.Retrieve(temp);
		cout<<"The ID of this Task is: "<<temp.GetID()<<endl;
		cout<<"The arrival time is: ";convertoHours(temp.GetArrivalTime());
		cout<<"The Task name is: "<<temp.GetName()<<endl;
		cout<<"The wait time for this task is: ";
		convertoHours(temp.GetWaiTtime());
		cout<<"This Task will start at: ";
		convertoHours(temp.GetStartTime());
		cout<<"The period Time of the Task is: "<<temp.GetPeriodTime()<<endl;
		cout<<"The priority of this Task is: "<<temp.GetPriority()<<endl<<endl;
		out.serve();
		c++;
	}
	if(c==0)
	cout<<"There is no Tasks in The Bank.\n";
	else
	cout<<"The number of the Task that not served yet and can be Done Today is: "<<c<<endl;
	c=0;
	cout<<"***************\n";
	while(!cannot.empty()){
		cannot.Retrieve(temp);
		cout<<"The ID of this Task is: "<<temp.GetID()<<endl;
		cout<<"The arrival time is: ";convertoHours(temp.GetArrivalTime());
		cout<<"The Task name is: "<<temp.GetName()<<endl;
		cout<<"The wait time for this task is: ";
		convertoHours(temp.GetWaiTtime());
		cout<<"This Task will start at: ";
		convertoHours(temp.GetStartTime());
		cout<<"The period Time of the Task is: "<<temp.GetPeriodTime()<<endl;
		cout<<"The priority of this Task is: "<<temp.GetPriority()<<endl<<endl;
		cannot.serve();
		c++;
	}
	if(c==0)
	cout<<"Every Task can be Done Today.\n";
	else
	cout<<c<<" Tasks not serverd and Can't be Done Today.\n";
}
void convertoHours(int x){
	int hours=x/60;
	x=x-hours*60;
	cout<<hours<<":"<<x<<endl;
}
template <typename T>
int size(queue <T>as){
	int c=0;
	while(!as.empty()){
		as.serve();
		c++;
	}
	return c;
}
template <typename T>
void Order(queue <T>&jer){
	if(!jer.empty()){
		int x=size(jer);
		Bank aa[x];
		for(int i=0;i<x;i++){
			jer.Retrieve(aa[i]);
			jer.serve();
		}
		
		for(int i=0;i<x;i++){
			for(int j=i;j<x;j++){
				if(aa[i].GetArrivalTime()>aa[j].GetArrivalTime()){
					Bank temp=aa[i];
					aa[i]=aa[j];
					aa[j]=temp;
				}
			}
		}
		for(int i=0;i<x;i++)
		jer.Append(aa[i]);
	}
}
template<typename T>
void AddRandomly(Bank temp[],int n,queue<T>temp1,queue<T>temp2,queue<T>temp3){
	int now=false,past=false,j,x=100+(size(temp1)+size(temp2)+size(temp3))*2;
	for(int i=0;i<n;i++){
		temp[i].SetID(rand()%100+1);
		int n=14*60-ClockTime;
		temp[i].SetArrivalTime(rand()%n+1+ClockTime);
		if(now==false || past==false){
			for(j=0;j<i;j++){
			while(temp[j].GetID()==temp[i].GetID()){
				temp[i].SetID(rand()%x+1);
			    now=true;
			}
		}
		while(CheckID(temp1,temp2,temp3,temp[i].GetID())==false){
			temp[i].SetID(rand()%x*2);
		}
		past=true;
		for(j=0;j<i;j++){
			if(temp[i].GetID()==temp[j].GetID())
			now=false;
			else
			now=true;
		}
		x=x*2;
		}
		string name;
		int per;
		PutTaskName(name,per,rand()%5+1);
		temp[i].SetName(name);
		temp[i].SetPeriod(per);
		PutPriority(name,rand()%3+1);
		temp[i].SetPriority(name);
	}
}
template <typename T>
void Rearrange(queue <T>&jer){
	Bank temp;
	queue <T>temp2;
	while(!jer.empty()){
		jer.Retrieve(temp);
		temp2.Append(temp);
		jer.serve();
	}
	while(!temp2.empty()){
		temp2.Retrieve(temp);
		if(compare(temp.GetPriority(),"Important Task")==true){
			if(temp.GetArrivalTime()>=ClockTime+2)
			temp.SetArrivalTime(temp.GetArrivalTime()-2);
			else
			temp.SetArrivalTime(ClockTime);
		}
		if(compare(temp.GetPriority(),"VIP Task")==true){
			if(temp.GetArrivalTime()>=ClockTime+5)
			temp.SetArrivalTime(temp.GetArrivalTime()-5);
			else
			temp.SetArrivalTime(ClockTime);
		}
		jer.Append(temp);
		temp2.serve();
	}
	
}
bool compare(string s1,string s2){
	int i;
	for(i=0;s1[i]!=NULL && s2[i]!=NULL;i++){
		if(s1[i]!=s2[i])
		return false;
	}
	if(s1[i]==NULL && s2[i]!=NULL)
	return false;
	if(s1[i]!=NULL && s2[i]==NULL)
	return false;
	return true;
}
template <typename T>
bool Right(queue <T>jer,int x){
	Bank temp;
	while(!jer.empty()){
		jer.Retrieve(temp);
		if(temp.GetID()==x){
			cout<<endl;
			cout<<"The Task ID is: "<<temp.GetID()<<endl;
	        cout<<"The Task Name is: "<<temp.GetName()<<endl;
           	cout<<"The Priority of this Task is: "<<temp.GetPriority()<<endl;
           	cout<<"The Period time of this Task is: ";
           	convertoHours(temp.GetPeriodTime());
           	cout<<"The Arrival time of the Task is: ";
         	convertoHours(temp.GetArrivalTime());
          	cout<<"The Waiting time for this Task is: ";
           	convertoHours(temp.GetWaiTtime());
         	cout<<"The Task will start at: ";
           	convertoHours(temp.GetStartTime());
          	cout<<endl;
          	return true;
		}
		jer.serve();
	}
	return false;
	
}
template <typename T>
void WaitTimeForTasks(queue <T>our,queue<T>sir,queue<T>cannot){
	if(our.empty() && sir.empty() && cannot.empty())
	cout<<"There is no Task yet.\n";
	else{
		int n=0;
	    Bank temp;
	    while(!our.empty()){
	      	our.Retrieve(temp);
	      	n+=temp.GetWaiTtime();
	      	our.serve();
	      }
	      while(!sir.empty()){
	      	sir.Retrieve(temp);
	      	n+=temp.GetWaiTtime();
	      	sir.serve();
	      }
	      if(cannot.empty()){
      		cout<<"The Total waiting time for all Tasks is: ";
      		convertoHours(n);
      	}
      	else{
	      	cout<<"The Total waiting time for all Tasks can be Done or have Done Today is: ";
	        convertoHours(n);
	        int z=0;
	        while(!cannot.empty()){
      		cannot.Retrieve(temp);
      		z+=temp.GetWaiTtime();
      		cannot.serve();
      	     }
      	    cout<<"The Total waiting time for all Tasks cannot be Done Today: ";
      	     cout<<"means they waiting time for tomorrow is: ";
      	      convertoHours(z);
      	      cout<<"The Total waiting time for all of them is: ";
      	      convertoHours(z+n);
	      }
	}
}
template <typename T>
void TimeToFinish(queue <T>our){
	if(our.empty())
	cout<<"The Bank is closed, see you tomorrow.\n";
	else{
		Bank temp;
		int n;
		while(!our.empty()){
			our.Retrieve(temp);
			n+=temp.GetPeriodTime();
			our.serve();
		}
	   cout<<"The Prtiod Time for all Task in The Bank is: ";
	   convertoHours(n);
	   cout<<endl;
	}
}
template <typename T>
void NotToday(queue <T>cannot){
	int x=0;
	while(!cannot.empty()){
		cannot.serve();
		x++;
	}
	if(x==0)
	cout<<"Every Task can be Done Today.\n";
	else
	cout<<x<<" Tasks can't be Done Today.\n";
}
template <typename T>
void ServedTasks(queue <T>Done){
	int x=0;
	Bank temp;
	while(!Done.empty()){
		Done.Retrieve(temp);
		x++;
		    cout<<"The Task ID is: "<<temp.GetID()<<endl;
	        cout<<"The Task Name is: "<<temp.GetName()<<endl;
           	cout<<"The Priority of this Task is: "<<temp.GetPriority()<<endl;
           	cout<<"The Period time of this Task is: ";
           	convertoHours(temp.GetPeriodTime());
           	cout<<"The Arrival time of the Task is: ";
         	convertoHours(temp.GetArrivalTime());
          	cout<<"The Waiting time for this Task is: ";
           	convertoHours(temp.GetWaiTtime());
         	cout<<"The has statred at: ";
           	convertoHours(temp.GetStartTime());
          	Done.serve();
          	cout<<"***************\n";
	}
	if(x==0)
	cout<<"There is no Task is Finished yet.\n";
	else
	cout<<x<<" Tasks is Finished Today.\n";
}
template <typename T>
void CarryOver(queue <T>&jer,queue <T>&cannot){
	Bank temp;
	queue <T>temp2;
	while(!jer.empty()){
		jer.Retrieve(temp);
		if(temp.GetStartTime()<14*60){
			temp2.Append(temp);
			jer.serve();
		}
		else{
			cannot.Append(temp);
			jer.serve();
		}
	}
	while(!temp2.empty()){
		temp2.Retrieve(temp);
		jer.Append(temp);
		temp2.serve();
	}
	Order(cannot);
	Bank temp4;
	cannot.Retrieve(temp4);
	if(temp4.GetArrivalTime()>=temp.GetStartTime()+temp.GetPeriodTime())
	PutTime(cannot,1,0);
	else
	PutTime(cannot,1,temp.GetStartTime()+temp.GetPeriodTime()-temp4.GetArrivalTime());
	
}
template <typename T>
bool CheckID(queue <T>temp1,queue<T>temp2,queue<T>temp3,int x){
	Bank temp4;
	while(!temp1.empty()){
		temp1.Retrieve(temp4);
		if(temp4.GetID()==x)
		return false;
		temp1.serve();
	}
	while(!temp2.empty()){
		temp2.Retrieve(temp4);
		if(temp4.GetID()==x)
		return false;
		temp2.serve();
	}
	while(!temp3.empty()){
		temp3.Retrieve(temp4);
		if(temp4.GetID()==x)
		return false;
		temp3.serve();
	}
	return true;
}
template <typename T>
void CarryOn(queue <T>&jer,queue <T>&cannot){
	Bank temp;
	Bank temp3;
	jer.Retrieve(temp3);
	queue <T>temp2;
		while(!cannot.empty()){
		cannot.Retrieve(temp);
		if(temp.GetStartTime()<=14*60-1){
			jer.Append(temp);
		}
		else
		temp2.Append(temp);
		cannot.serve();
	}
	while(!temp2.empty()){
		temp2.Retrieve(temp);
		cannot.Append(temp);
		temp2.serve();
	}
	Order(jer);
	PutTime(jer,1,temp3.GetWaiTtime());
}

