#include<iostream>
#include<string>
#include<queue>
#include<vector>
#include<map>
#include<sstream>
#include<algorithm>

using namespace std;

class Packet
{

	private :
	    int packetNumber;
		int packetId;
	    string sourceIp;
	    string destinationIp;
	    int size;
	    int priority;
	    int ttl;
	    vector<string> history;
	    
	public :
		
	 
		Packet()
		{
			packetNumber=0;
			packetId=0;
			sourceIp="";
			destinationIp="";
			size=0;
			priority=0;
			ttl=5;
		}    
		
		Packet(int packetNumber,int packetId,string sourceIp,string destinationIp,int size,int priority,int ttl)
		{
			this->packetNumber=packetNumber;
			this->packetId=packetId;
			this->sourceIp=sourceIp;
			this->destinationIp=destinationIp;
			this->size=size;
			this->priority=priority;
			this->ttl=ttl;
		}
		
	int getPacketNumber() const{
		return packetNumber;
	}
	
	int getPriority() const{
		return priority;
	}	
	
	string getDestinationIp() const
    {
    return destinationIp;
    }
    
    int getTTL() const
    {
    	return ttl;
	}
    
    void decreaseTTL(){
    	ttl--;
	}
	
	void addHistory(const string& entry)
    {
    history.push_back(entry);
    }
	
	void displayHistory() const
    {
    cout << "\n========== PACKET HISTORY ==========" << endl;

    if(history.empty())
    {
        cout << "No history available." << endl;
        return;
    }

    for(const string& entry : history)
    {
        cout << entry << endl;
    }
    }

	void display() const 
	{
		
		cout<<endl;
		cout<<"Next Packet :"<<endl;
		cout<<"Packet "<<packetNumber<<endl;
		cout<<"Packet ID : "<<packetId<<endl;
		cout<<"Source IP : "<<sourceIp<<endl;
		cout<<"Destination IP : "<<destinationIp<<endl;
		cout<<"Size : "<<size<<" bytes"<<endl;
		cout<<"Priority : "<<priority<<endl;
		cout<<"TTL : "<<ttl<<endl;
		cout<<endl;
		
	
	}
	
	};
	
	
	struct PacketCompare
{
	bool operator()(const Packet& a,const Packet& b) const{
		if(a.getPriority()==b.getPriority()){
			return a.getPacketNumber()>b.getPacketNumber();
		}
		return a.getPriority()>b.getPriority();
	}
};
    class Router;
    
    struct Route
{
    string network;
    int prefixLength;
    Router* nextHop;
};

struct Connection
{
    Router* routerA;
    Router* routerB;
};

bool ipToInt(const string& ip, unsigned int& result)
{
    unsigned int a, b, c, d;
    char dot1, dot2, dot3;

    stringstream ss(ip);

    if(!(ss >> a >> dot1 >> b >> dot2 >> c >> dot3 >> d))
    {
        return false;
    }

    if(dot1 != '.' || dot2 != '.' || dot3 != '.')
    {
        return false;
    }

    if(a > 255 || b > 255 || c > 255 || d > 255)
    {
        return false;
    }

    result = (a << 24) |
             (b << 16) |
             (c << 8)  |
             d;

    return true;
}

bool isValidIP(const string& ip)
{
    unsigned int value;
    return ipToInt(ip, value);
}

unsigned int createMask(int prefixLength)
{
    if(prefixLength < 0 || prefixLength > 32)
    {
        return 0;
    }

    if(prefixLength == 0)
    {
        return 0;
    }

    return 0xFFFFFFFFu << (32 - prefixLength);
}

bool matchesCIDR(const string& ip,
                 const string& network,
                 int prefixLength)
{
    unsigned int ipValue;
    unsigned int networkValue;

    if(!ipToInt(ip, ipValue))
    {
        return false;
    }

    if(!ipToInt(network, networkValue))
    {
        return false;
    }

    unsigned int mask = createMask(prefixLength);

    return (ipValue & mask) == (networkValue & mask);
}

	class Router
	{
		private :
			   	priority_queue<Packet, vector<Packet>, PacketCompare> packetQueue;
			   	
			   	vector<Route> routingTable;
				   
				   	
				const int MAX_CAPACITY; 
				int routerId;  
		
		public :
	
	           Router(int routerId):MAX_CAPACITY(5)
			   {
	           	this->routerId=routerId;
	           	
			   }
			   
			   bool isEmpty() const
               {
                 return packetQueue.empty();
               }
			   
			     Packet getFrontPacket() const
               {
                   return packetQueue.top();
               }
               
			   bool addPacket(const Packet& p)
			   {
			   	   if(packetQueue.size()<MAX_CAPACITY)
				   {
					packetQueue.push(p);
				
					cout<<"Packet added successfully!"<<endl;
					   return true;
					}else{
						cout<<"Queue is Full!"<<endl<<"Packet cannot be added."<<endl;
			           return false;
					}
			   }
			   bool receivePacket(const Packet& p)
{
    if(packetQueue.size() < MAX_CAPACITY)
    {
        packetQueue.push(p);
        return true;
    }

    cout << "Destination Router Queue is Full!" << endl;
    return false;
}
              
              
			   bool processPacket(){
			   	 if(packetQueue.empty()){
	                	cout<<"Queue is Empty"<<endl;
	                	  return false;
	            	}else{
			            cout<<"Queue contains Packets"<<endl;
			          
	             	}
	             	packetQueue.top().display();
				    cout<<"Processing Packet... "<<packetQueue.top().getPacketNumber()<<endl;
				   	cout<<"Packet "<<packetQueue.top().getPacketNumber()<<" processed successfully."<<endl;
				    packetQueue.pop();
				  
				    return true;
			   }
			   
			   void displayFront()
			   {
			   		 if(packetQueue.empty()){
	                	cout<<"Router "<<routerId<<" : Queue is Empty"<<endl;
	                	  return;
	            	}else{
			            cout<<"Router "<<routerId<<endl;
			          
	             	}
	             	
					packetQueue.top().display();
			   }	
			   
			   void displayQueueSize()
			   {
			   		cout<<"Queue Size : "<<packetQueue.size()<<endl;
			   }	
			 
			   
			   void removeFront()
               {
                  if(packetQueue.empty())
                  {
                    cout << "Queue is Empty" << endl;
                    return; 
                  }

                   packetQueue.pop();
               }
               
               bool displayPacketHistory(int packetNumber) const
{
    priority_queue<Packet, vector<Packet>, PacketCompare> temp = packetQueue;

    while(!temp.empty())
    {
        Packet p = temp.top();

        if(p.getPacketNumber() == packetNumber)
        {
            p.displayHistory();
            return true;
        }

        temp.pop();
    }

    return false;
}
               
               bool dropPacket()
              {
                if(packetQueue.empty())
                {
                 cout << "Queue is Empty" << endl;
                 return false;
                }
                packetQueue.pop();
              
                
                return true;
             }
               
void addRoute(string network, int prefixLength, Router* destinationRouter)
{
    for(Route& route : routingTable)
    {
        if(route.network == network &&
           route.prefixLength == prefixLength)
        {
            route.nextHop = destinationRouter;
            return;
        }
    }

    Route route;

    route.network = network;
    route.prefixLength = prefixLength;
    route.nextHop = destinationRouter;

    routingTable.push_back(route);
}

bool removeRoute(string network, int prefixLength)
{
    for(auto it = routingTable.begin(); it != routingTable.end(); ++it)
    {
        if(it->network == network &&
           it->prefixLength == prefixLength)
        {
            routingTable.erase(it);
            return true;
        }
    }

    return false;
}

 void displayRoutingTable() const
{
    cout << "\nRouter " << routerId << " Routing Table:" << endl;

    if(routingTable.empty())
    {
        cout << "Routing Table is Empty!" << endl;
        return;
    }

    for(const Route& route : routingTable)
    {
        cout << route.network << "/" << route.prefixLength<< " -> Router "
             << route.nextHop->getRouterId() << endl;
    }
}
                
                int getQueueSize() const
                {
                   return packetQueue.size();
                }   
                
                int getRouterId() const
               {
                   return routerId;
               }
               
               void displayPackets() const
                {
               if(packetQueue.empty())
               {
                 cout << "  Empty" << endl;
                return;
               }

             priority_queue<Packet, vector<Packet>, PacketCompare> temp = packetQueue;

             while(!temp.empty())
            {
             Packet p = temp.top();

             cout << "  Packet "<< p.getPacketNumber()<< " | Destination: " << p.getDestinationIp() <<
			  " | Priority: "<< p.getPriority()<< " | TTL: "<< p.getTTL()<< endl;
      
	        temp.pop();
            }
                }
               
               
        Router* findRoute(const Packet& p) const
{
    string destinationIP = p.getDestinationIp();

    Router* bestRouter = nullptr;
    int longestPrefix = -1;

    for(const Route& route : routingTable)
    {
        if(matchesCIDR(destinationIP,
                       route.network,
                       route.prefixLength))
        {
            if(route.prefixLength > longestPrefix)
            {
                longestPrefix = route.prefixLength;
                bestRouter = route.nextHop;
            }
        }
    }

    return bestRouter;
}
           
           
	};
	
	class Network
{
private:
    int packetsAdded;
    int packetsProcessed;
    int packetsDropped;
    vector<Packet> completedPackets;
    vector<Router*> routers;
    vector<Connection> connections;
public:

    Network()
    {
        packetsAdded = 0;
        packetsProcessed = 0;
        packetsDropped = 0;
    }
    
    ~Network()
   {
    for(Router* router : routers)
    {
        delete router;
    }

    routers.clear();
  }


    void packetAdded()
    {
        packetsAdded++;
    }

    void packetProcessed()
    {
        packetsProcessed++;
    }

    void packetDropped()
    {
        packetsDropped++;
    }
    
    void saveCompletedPacket(const Packet& p)
{
    completedPackets.push_back(p);
}

    void displayStatistics(int queueSize)
    {
        cout << "\n======== NETWORK PACKET STATISTICS ========" << endl;
        cout << "Packets Added     : " << packetsAdded << endl;
        cout << "Packets Processed : " << packetsProcessed << endl;
        cout << "Packets Dropped   : " << packetsDropped << endl;
        cout << "Packets in Queue  : " << queueSize << endl;
    }
    
    int getTotalQueueSize() const
{
    int total = 0;

    for(Router* router : routers)
    {
        if(router != nullptr)
        {
            total += router->getQueueSize();
        }
    }

    return total;
}

    
    bool displayCompletedPacketHistory(int packetNumber) const
{
    for(const Packet& p : completedPackets)
    {
        if(p.getPacketNumber() == packetNumber)
        {
            p.displayHistory();
            return true;
        }
    }

    return false;
}

void addRouter(Router* router)
{
    if(router == nullptr)
    {
        return;
    }

    if(getRouterById(router->getRouterId()) != nullptr)
    {
        return;
    }

    routers.push_back(router);
}


   Router* getRouterById(int id) const
{
    for(Router* router : routers)
    {
        if(router != nullptr &&
           router->getRouterId() == id)
        {
            return router;
        }
    }

    return nullptr;
}

   Router* createRouter(int id)
{
    if(getRouterById(id) != nullptr)
    {
        return nullptr;
    }

    Router* newRouter = new Router(id);

    routers.push_back(newRouter);

    return newRouter;
}

    bool connectRouters(int id1, int id2)
{
    Router* routerA = getRouterById(id1);
    Router* routerB = getRouterById(id2);

    if(routerA == nullptr || routerB == nullptr)
    {
        return false;
    }

    if(routerA == routerB)
    {
        return false;
    }

    for(const Connection& connection : connections)
    {
        if((connection.routerA == routerA &&
            connection.routerB == routerB) ||
           (connection.routerA == routerB &&
            connection.routerB == routerA))
        {
            return false;
        }
    }

    Connection connection;
    connection.routerA = routerA;
    connection.routerB = routerB;

    connections.push_back(connection);

    return true;
}

bool disconnectRouters(int id1, int id2)
{
    Router* routerA = getRouterById(id1);
    Router* routerB = getRouterById(id2);

    if(routerA == nullptr || routerB == nullptr)
    {
        return false;
    }

    for(auto it = connections.begin(); it != connections.end(); ++it)
    {
        if((it->routerA == routerA &&
            it->routerB == routerB) ||
           (it->routerA == routerB &&
            it->routerB == routerA))
        {
            connections.erase(it);
            return true;
        }
    }

    return false;
}


void displayTopology() const
{
    cout << "\n========== NETWORK TOPOLOGY ==========" << endl;

    if(connections.empty())
    {
        cout << "No connections available." << endl;
        return;
    }

    for(const Connection& connection : connections)
    {
        cout << "Router "
             << connection.routerA->getRouterId()
             << " <----> Router "
             << connection.routerB->getRouterId()
             << endl;
    }

    cout << "=======================================" << endl;
}

void displayRouters() const
{
    cout << "\n========== AVAILABLE ROUTERS ==========" << endl;

    for(Router* router : routers)
    {
        if(router != nullptr)
        {
            cout << "Router " << router->getRouterId() << endl;
        }
    }

    cout << "=======================================" << endl;
}


void displayNetworkStatus() const
{
    cout << "\n======== NETWORK STATUS ========" << endl;

    for(Router* router : routers)
    {
        if(router != nullptr)
        {
            cout << "\nRouter " << router->getRouterId() << endl;
            router->displayPackets();
        }
    }

    cout << "\n================================" << endl;
}

bool displayActivePacketHistory(int packetNumber) const
{
    for(Router* router : routers)
    {
        if(router != nullptr)
        {
            if(router->displayPacketHistory(packetNumber))
            {
                return true;
            }
        }
    }

    return false;
}


void displayAllRoutingTables() const
{
    cout << "\n========== ROUTING TABLES ==========" << endl;

    for(Router* router : routers)
    {
        if(router != nullptr)
        {
            router->displayRoutingTable();
        }
    }

    cout << "====================================" << endl;
}  

   bool areConnected(int id1, int id2) const
{
    Router* routerA = getRouterById(id1);
    Router* routerB = getRouterById(id2);

    if(routerA == nullptr || routerB == nullptr)
    {
        return false;
    }

    for(const Connection& connection : connections)
    {
        if((connection.routerA == routerA &&
            connection.routerB == routerB) ||
           (connection.routerA == routerB &&
            connection.routerB == routerA))
        {
            return true;
        }
    }

    return false;
}


vector<int> findPath(int sourceId, int destinationId) const
{
    vector<int> path;

    Router* source = getRouterById(sourceId);
    Router* destination = getRouterById(destinationId);

    if(source == nullptr || destination == nullptr)
    {
        return path;
    }

    if(sourceId == destinationId)
    {
        path.push_back(sourceId);
        return path;
    }

    queue<int> q;
    vector<int> visited;
    map<int, int> parent;

    q.push(sourceId);
    visited.push_back(sourceId);
    parent[sourceId] = -1;

    while(!q.empty())
    {
        int currentId = q.front();
        q.pop();

        for(const Connection& connection : connections)
        {
            int neighbourId = -1;

            if(connection.routerA->getRouterId() == currentId)
            {
                neighbourId = connection.routerB->getRouterId();
            }
            else if(connection.routerB->getRouterId() == currentId)
            {
                neighbourId = connection.routerA->getRouterId();
            }

            if(neighbourId == -1)
            {
                continue;
            }

            bool alreadyVisited = false;

            for(int id : visited)
            {
                if(id == neighbourId)
                {
                    alreadyVisited = true;
                    break;
                }
            }

            if(alreadyVisited)
            {
                continue;
            }

            visited.push_back(neighbourId);
            parent[neighbourId] = currentId;

            if(neighbourId == destinationId)
            {
                int current = destinationId;

                while(current != -1)
                {
                    path.push_back(current);
                    current = parent[current];
                }

                reverse(path.begin(), path.end());

                return path;
            }

            q.push(neighbourId);
        }
    }

    return path;
}

};


int getIntegerInput(const string& message)
{
    string input;

    while(true)
    {
        cout << message;
        cin >> input;

        stringstream ss(input);

        int value;

        if(ss >> value)
        {
            char extra;

            if(!(ss >> extra))
            {
                return value;
            }
        }

        cout << "Invalid input! Please enter a valid integer." << endl;
    }
}


	int main()
   {
  
	
		
		int packetNumber;
		int packetId;
	    string sourceIp;
	    string destinationIp;
	    int size;
	    int priority;
	    int choice;
	    int routerChoice;
        int ttl;
	
	  Network network;

Router* r1 = network.createRouter(1);
Router* r2 = network.createRouter(2);
Router* r3 = network.createRouter(3);
Router* r4 = network.createRouter(4);

network.connectRouters(1, 2);
network.connectRouters(2, 3);
network.connectRouters(1, 4);
network.connectRouters(4, 3);
       
     r1->addRoute("192.168.1.0", 24, r1);
r1->addRoute("192.168.2.0", 24, r2);
r1->addRoute("192.168.3.0", 24, r2);
r1->addRoute("0.0.0.0", 0, r3);

r2->addRoute("192.168.1.0", 24, r1);
r2->addRoute("192.168.2.0", 24, r2);
r2->addRoute("192.168.3.0", 24, r3);

r3->addRoute("192.168.1.0", 24, r1);
r3->addRoute("192.168.2.0", 24, r2);
r3->addRoute("192.168.3.0", 24, r3);

       
       Router* selectedRouter=nullptr;
      
		cout<<"==========Network Packet Simulator==========\n";
	
		do
		{
			cout<<"\n1.Add Packet\n"<<"2.Process Packet\n"<<"3.Display Front Packet\n"
			<<"4.Queue Size\n"<<"5.Packet Statistics\n"<<"6.Forward Packet\n"
			<<"7.Network Status\n"<<"8.Display Routing Tables\n"<<"9.Packet History\n"
			<<"10.Add Route\n"<<"11.Remove Route\n"<<"12.Display Network Topology\n"
			<<"13.Disconnect Routers\n"<<"14.Exit"<<endl;
			
			cout<<endl;
			
		    choice = getIntegerInput("Enter Choice : ");
			
		switch(choice)
			{
				case 1:
					{
	   	    packetNumber = getIntegerInput("Enter the Packet Number : ");
            packetId = getIntegerInput("Enter Packet ID : ");
            cout<<"Enter Source IP : ";
            cin >> sourceIp;
            cout<<"Enter Destination IP : ";
            cin >> destinationIp;
            if(!isValidIP(sourceIp))
            {
            cout << "Invalid Source IP!" << endl;
            break;
            }

            if(!isValidIP(destinationIp))
            {
            cout << "Invalid Destination IP!" << endl;
            break;
            }
            
            size = getIntegerInput("Enter size : ");
            priority = getIntegerInput("Enter Priority : ");
            ttl = getIntegerInput("Enter TTL : ");
	     	
	     	
	     	if(packetNumber>0 && packetId>0 && size>0 && priority>=1 && priority<=3 && ttl>0){
			 
	      	Packet p(packetNumber,packetId,sourceIp,destinationIp,size,priority,ttl);
	      	
	      	network.displayRouters();
           
            routerChoice = getIntegerInput("Enter Router ID: ");

	     selectedRouter = network.getRouterById(routerChoice);
	      
	      if(selectedRouter != nullptr)
{
    if(selectedRouter->addPacket(p))
    {
        network.packetAdded();
    }
    else
    {
        network.packetDropped();
    }
}
else
{
    cout << "Invalid Router!" << endl;
}
				
	      }else{
	      	if(packetNumber<=0){
	      		cout<<"Entered Packet Number is Invalid!"<<endl;
			  }else if(packetId<=0){
			    cout<<"Entered Packet ID is Invalid!"<<endl;
			  }else if(size<=0){
			    cout<<"Entered Size is Invalid!"<<endl;	
			}else if(priority < 1 || priority > 3)
{
    cout << "Entered Priority is Invalid!" << endl;
}
else if(ttl <= 0)
{
    cout << "Entered TTL is Invalid!" << endl;
}
			 
		  }
	      	     break;
				}
				    
	case 2:
					
    network.displayRouters();
    
    routerChoice = getIntegerInput("Enter Router ID: ");
    
  selectedRouter = network.getRouterById(routerChoice);

    if(selectedRouter!=nullptr){
    	if(selectedRouter->processPacket()){
    		network.packetProcessed();
			}
	}
    else
    {
        cout << "Invalid Router!" << endl;
    }
	     break;
	     
	     
	case 3:
				
   network.displayRouters();

   routerChoice = getIntegerInput("Enter Router ID: ");
   
   selectedRouter = network.getRouterById(routerChoice);
    
    if(selectedRouter!=nullptr)
    {
       selectedRouter->displayFront();
    }
    else
    {
        cout << "Invalid Router!" << endl;
    }
      
    break;
    
    
	case 4:
				
     network.displayRouters();

    routerChoice = getIntegerInput("Enter Router ID: ");
    
    selectedRouter = network.getRouterById(routerChoice);
    
    if(selectedRouter!=nullptr)
    {
         selectedRouter->displayQueueSize();
    }
    else
    {
        cout << "Invalid Router!" << endl;
    }
      
    break;
				
   case 5:
{
    int totalQueueSize = network.getTotalQueueSize();

    network.displayStatistics(totalQueueSize);

    break;
}
    
  case 6:
{
    network.displayRouters();

    int sourceRouterChoice =
        getIntegerInput("Enter Source Router ID: ");

    Router* sourceRouter =
        network.getRouterById(sourceRouterChoice);

    if(sourceRouter == nullptr)
    {
        cout << "Invalid Source Router!" << endl;
        break;
    }

    if(sourceRouter->isEmpty())
    {
        cout << "Source Router is Empty!" << endl;
        break;
    }

    Packet p = sourceRouter->getFrontPacket();

    /*
        Find the router selected by the routing table.
    */
    Router* destinationRouter =
        sourceRouter->findRoute(p);

    if(destinationRouter == nullptr)
    {
        cout << "Unknown Destination IP!" << endl;
        break;
    }

    /*
        If the routing table points to the current router,
        the packet has reached its destination.
    */
    if(sourceRouter == destinationRouter)
    {
        string routerName =
            "Router " +
            to_string(sourceRouter->getRouterId());

        p.addHistory(
            routerName + " | DESTINATION REACHED"
        );

        cout << "Packet has reached its destination!"
             << endl;

        p.addHistory(
            routerName + " | PACKET PROCESSED"
        );

        network.saveCompletedPacket(p);

        if(sourceRouter->processPacket())
        {
            network.packetProcessed();
        }

        break;
    }

    /*
        Check whether the routing-table next hop
        is directly connected.
    */
    if(!network.areConnected(
           sourceRouter->getRouterId(),
           destinationRouter->getRouterId()))
    {
        cout << "Next hop is unavailable." << endl;
        cout << "Searching for alternate path..." << endl;

        /*
            Find the complete physical path from the
            current router to the router selected by
            the routing table.
        */
        vector<int> path =
            network.findPath(
                sourceRouter->getRouterId(),
                destinationRouter->getRouterId()
            );

        if(path.size() < 2)
        {
            cout << "No alternate path available!"
                 << endl;
            break;
        }

        cout << "Alternate path found: ";

        for(size_t i = 0; i < path.size(); i++)
        {
            cout << "R" << path[i];

            if(i < path.size() - 1)
            {
                cout << " -> ";
            }
        }

        cout << endl;

        /*
            IMPORTANT:
            Instead of forwarding only to path[1] and then
            recalculating the route from that router,
            follow the complete physical path.

            Example:

            R2 -> R1 -> R4 -> R3

            The packet will be forwarded through each hop.
        */

        if(p.getTTL() <= 1)
        {
            string routerName =
                "Router " +
                to_string(sourceRouter->getRouterId());

            p.addHistory(
                routerName + " | TTL EXPIRED"
            );

            p.addHistory(
                routerName + " | PACKET DROPPED"
            );

            network.saveCompletedPacket(p);

            cout << "TTL expired. Packet dropped!"
                 << endl;

            if(sourceRouter->dropPacket())
            {
                network.packetDropped();
            }

            break;
        }

        /*
            Remove the packet from the source router only
            after we know that an alternate path exists.
        */
        sourceRouter->removeFront();

        Router* currentRouter = sourceRouter;

        bool forwardingFailed = false;

        /*
            Follow the BFS path one hop at a time.
        */
        for(size_t i = 1; i < path.size(); i++)
        {
            Router* nextRouter =
                network.getRouterById(path[i]);

            if(nextRouter == nullptr)
            {
                forwardingFailed = true;
                break;
            }

            if(!network.areConnected(
                   currentRouter->getRouterId(),
                   nextRouter->getRouterId()))
            {
                cout << "Path became unavailable!"
                     << endl;

                forwardingFailed = true;
                break;
            }

            /*
                Check TTL before this hop.
            */
            if(p.getTTL() <= 1)
            {
                string routerName =
                    "Router " +
                    to_string(
                        currentRouter->getRouterId()
                    );

                p.addHistory(
                    routerName + " | TTL EXPIRED"
                );

                p.addHistory(
                    routerName + " | PACKET DROPPED"
                );

                network.saveCompletedPacket(p);

                cout << "TTL expired. Packet dropped!"
                     << endl;

                network.packetDropped();

                forwardingFailed = true;
                break;
            }

            int oldTTL = p.getTTL();

            p.decreaseTTL();

            int newTTL = p.getTTL();

            string historyEntry =
                "Router " +
                to_string(
                    currentRouter->getRouterId()
                );

            historyEntry +=
                " -> Router " +
                to_string(
                    nextRouter->getRouterId()
                );

            historyEntry +=
                " | TTL: " +
                to_string(oldTTL) +
                " -> " +
                to_string(newTTL);

            p.addHistory(historyEntry);

            /*
                Put the packet into the next router.
            */
            if(!nextRouter->receivePacket(p))
            {
                cout << "Packet could not be forwarded."
                     << endl;

                forwardingFailed = true;
                break;
            }

            /*
                Remove the temporary copy from the next
                router before continuing to the next hop.

                The packet will ultimately remain at the
                final router.
            */
            if(i < path.size() - 1)
            {
                nextRouter->removeFront();
            }

            cout << "Packet forwarded: Router "
                 << currentRouter->getRouterId()
                 << " -> Router "
                 << nextRouter->getRouterId()
                 << endl;

            currentRouter = nextRouter;
        }

        if(forwardingFailed)
        {
            break;
        }

        /*
            The final router in the BFS path has been reached.
        */
        Router* finalRouter = currentRouter;

        if(finalRouter->getRouterId() ==
           destinationRouter->getRouterId())
        {
            p.addHistory(
                "Router " +
                to_string(finalRouter->getRouterId()) +
                " | DESTINATION REACHED"
            );

            cout << "Packet has reached its destination!"
                 << endl;

            p.addHistory(
                "Router " +
                to_string(finalRouter->getRouterId()) +
                " | PACKET PROCESSED"
            );

            /*
                The packet is already in the final router's
                queue. Process it normally.
            */
            if(finalRouter->processPacket())
            {
                network.packetProcessed();
            }

            /*
                Save the completed packet with its history.
            */
            network.saveCompletedPacket(p);
        }

        break;
    }

    /*
        Normal direct forwarding.
    */
    if(p.getTTL() <= 1)
    {
        string routerName =
            "Router " +
            to_string(sourceRouter->getRouterId());

        p.addHistory(
            routerName + " | TTL EXPIRED"
        );

        p.addHistory(
            routerName + " | PACKET DROPPED"
        );

        network.saveCompletedPacket(p);

        cout << "TTL expired. Packet dropped!"
             << endl;

        if(sourceRouter->dropPacket())
        {
            network.packetDropped();
        }

        break;
    }

    cout << "\nDestination IP : "
         << p.getDestinationIp() << endl;

    cout << "Packet will be forwarded to Router "
         << destinationRouter->getRouterId()
         << endl;

    int oldTTL = p.getTTL();

    p.decreaseTTL();

    int newTTL = p.getTTL();

    string historyEntry =
        "Router " +
        to_string(sourceRouter->getRouterId());

    historyEntry +=
        " -> Router " +
        to_string(destinationRouter->getRouterId());

    historyEntry +=
        " | TTL: " +
        to_string(oldTTL) +
        " -> " +
        to_string(newTTL);

    p.addHistory(historyEntry);

    if(destinationRouter->receivePacket(p))
    {
        sourceRouter->removeFront();

        cout << "Packet forwarded successfully!"
             << endl;
    }
    else
    {
        cout << "Packet could not be forwarded."
             << endl;
    }

    break;
}

		
       case 7:
     
{
    network.displayNetworkStatus();
    break;
}
      
		case 8:
{
    network.displayAllRoutingTables();
    break;
}
   
case 9:
{
    int searchPacketNumber;

   searchPacketNumber = getIntegerInput("\nEnter Packet Number : ");

    bool found = network.displayActivePacketHistory(searchPacketNumber);

    if(!found)
    {
        found = network.displayCompletedPacketHistory(searchPacketNumber);
    }

    if(!found)
    {
        cout << "Packet not found in the network." << endl;
    }

    break;
}


  case 10:
{
    int routerId;
    int nextHopId;
    string routeNetwork;
    int prefixLength;

    routerId = getIntegerInput("Enter Router ID: ");


    Router* router = network.getRouterById(routerId);

    if(router == nullptr)
    {
        cout << "Router not found!" << endl;
        break;
    }

    cout << "Enter Network Address: ";
    cin >> routeNetwork;
    
    if(!isValidIP(routeNetwork))
{
    cout << "Invalid Network Address!" << endl;
    break;
}

    prefixLength = getIntegerInput("Enter Prefix Length: ");

    if(prefixLength < 0 || prefixLength > 32)
    {
        cout << "Invalid Prefix Length!" << endl;
        break;
    }

    cout << "Enter Next Hop Router ID: ";
    cin >> nextHopId;

    Router* nextHop = network.getRouterById(nextHopId);

    if(nextHop == nullptr)
    {
        cout << "Next Hop Router not found!" << endl;
        break;
    }
    
    if(routerId != nextHopId &&
	        !network.areConnected(routerId, nextHopId))
{
    cout << "Route cannot be added: Routers are not directly connected!" << endl;
    break;
}

    router->addRoute(routeNetwork, prefixLength, nextHop);

    cout << "Route added successfully!" << endl;

    break;
}


case 11:
{
    int routerId;
    string routeNetwork;
    int prefixLength;

    routerId = getIntegerInput("Enter Router ID: ");

    Router* router = network.getRouterById(routerId);

    if(router == nullptr)
    {
        cout << "Router not found!" << endl;
        break;
    }

    cout << "Enter Network Address: ";
    cin >> routeNetwork;

    prefixLength = getIntegerInput("Enter Prefix Length: ");

    if(prefixLength < 0 || prefixLength > 32)
    {
        cout << "Invalid Prefix Length!" << endl;
        break;
    }

    bool removed = router->removeRoute(routeNetwork, prefixLength);

    if(removed)
    {
        cout << "Route removed successfully!" << endl;
    }
    else
    {
        cout << "Route not found!" << endl;
    }

    break;
}

case 12:
	{
		network.displayTopology();
		break;
	}
	
	case 13:
{
    int routerId1;
    int routerId2;

    routerId1 = getIntegerInput("Enter First Router ID: ");
    routerId2 = getIntegerInput("Enter Second Router ID: ");

    if(network.disconnectRouters(routerId1, routerId2))
    {
        cout << "Routers disconnected successfully!" << endl;
    }
    else
    {
        cout << "Connection not found or invalid router!" << endl;
    }

    break;
}

	case 14:
		
	cout<<"Exiting..."<<endl;
	break;
					
	default:
	cout<<"Invalid choice!!!"<<endl;
	
					
	}
	
	}while(choice!=14);
	    
		return 0;
		
	}
	
	
	

