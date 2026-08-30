# Network Packet Simulator

A C++ project that simulates how packets move through a network of routers. The project combines Data Structures and Computer Networking concepts to handle packet scheduling, routing, forwarding, router connections, and network failures.

The simulator is menu-driven and allows different network operations to be performed and tested.

---

## About the Project

The Network Packet Simulator represents a small network made up of routers and connections between them.

Each router has its own packet queue and routing table. Packets contain information such as their source and destination IP addresses, packet size, priority, and TTL.

The program supports normal packet forwarding as well as recovery when a configured next-hop router is unavailable. In such cases, BFS is used to find an alternate path through the network.

The project was developed to understand how data structures and networking concepts can work together in a practical application.

---

## Features

### Packet Management

- Add packets to routers
- Store packets using a priority queue
- Process packets according to priority
- Display the front packet
- Display queue size
- Remove packets
- Drop packets
- Limit router queue capacity
- Maintain packet history
- Store completed packet information

### Packet Information

Each packet contains:

- Packet Number
- Packet ID
- Source IP Address
- Destination IP Address
- Packet Size
- Priority
- TTL
- Packet History

### Routing

The simulator provides routing tables for routers.

Each route contains:

- Network address
- Prefix length
- Next-hop router

The routing system supports:

- CIDR-based IPv4 matching
- Longest Prefix Matching (LPM)
- Default routes
- Adding routes
- Removing routes
- Displaying routing tables
- Selecting the appropriate next-hop router

### Packet Forwarding

Packets can be forwarded from one router to another according to the routing table.

The forwarding process checks the selected next hop and the connection between routers before forwarding the packet.

The packet history is updated as the packet moves through the network.

When the packet reaches the appropriate destination router, it can be processed successfully.

### Router Connections

The network supports:

- Creating router connections
- Checking whether two routers are connected
- Disconnecting routers
- Displaying the current network topology
- Displaying network status

### Failure Recovery

If the normal next-hop router is unavailable, the simulator searches for an alternate path using Breadth First Search (BFS).

For example:

```text
R2 -> R3
```

If the connection between R2 and R3 is unavailable, the simulator can find:

```text
R2 -> R1 -> R4 -> R3
```

The packet is then forwarded through the routers in the alternate path.

If no alternate path exists, the program reports that the destination cannot be reached through the available network.

### TTL Management

Each packet has a Time To Live (TTL).

The TTL is decreased while the packet is being forwarded. This prevents packets from continuing through the network indefinitely.

If the TTL expires, the packet is dropped and the event is recorded in its history.

### Packet History

The simulator keeps track of the movement of packets.

A packet history can contain information such as:

```text
Router 2 -> Router 1
Router 1 -> Router 4
Router 4 -> Router 3
Destination reached
Packet processed
```

This makes it possible to trace the path taken by a packet.

The program also keeps completed packet information so that packet history can be searched later.

### Network Statistics

The program maintains packet statistics including:

- Packets added
- Packets processed
- Packets dropped
- Packets currently in queues

### Input Validation

The program validates different types of user input, including:

- Integer values
- Router IDs
- Packet values
- Packet size
- Priority
- TTL
- IP addresses
- Prefix lengths
- Routing information
- Router connections

Invalid input is rejected and the user is asked to enter a valid value.

---

## Data Structures Used

| Data Structure | Purpose |
|---|---|
| Priority Queue | Stores packets according to priority |
| Vector | Stores routers, routes, connections, history, and completed packets |
| Queue | Used for BFS traversal |
| Map | Stores parent relationships during BFS |
| Graph | Represents connections between routers |
| Stringstream | Used for input parsing and validation |

---

## Algorithms Used

### Priority Queue

A priority queue is used at each router to manage packets.

Packets with higher priority are processed first. When packets have the same priority, the packet number is used to determine their order.

### CIDR Matching

The simulator supports CIDR network notation such as:

```text
192.168.3.0/24
```

The destination IP address and network address are converted into integer representations and compared using a subnet mask.

### Longest Prefix Matching

When more than one route matches a destination IP address, the route with the longest prefix is selected.

For example:

```text
192.168.2.0/24
192.168.2.128/25
```

For a destination such as:

```text
192.168.2.150
```

the `/25` route is more specific and is selected over the `/24` route.

### Breadth First Search

BFS is used to find an alternate path when the configured next-hop router is unavailable.

Example:

```text
R2 -> R1 -> R4 -> R3
```

The path is reconstructed and the packet is forwarded through the routers in the recovered path.

### TTL Handling

The TTL is decreased during packet forwarding. If the TTL reaches its expiration condition, the packet is dropped.

---

## System Architecture

The project is mainly organized around three classes:

```text
                 NETWORK PACKET SIMULATOR
                           |
          +----------------+----------------+
          |                |                |
        Packet           Router           Network
                           |                |
                    +------+-----+     +----+----+
                    |            |     |         |
              Priority Queue  Routing  Routers  Connections
                              Table
```

### Packet

The Packet class is responsible for:

- Storing packet details
- Managing TTL
- Maintaining packet history
- Displaying packet information

### Router

The Router class is responsible for:

- Maintaining packet queues
- Adding packets
- Receiving packets
- Processing packets
- Dropping packets
- Maintaining routing tables
- Adding and removing routes
- Finding routes using LPM
- Displaying router information

### Network

The Network class is responsible for:

- Managing routers
- Finding routers
- Managing connections
- Disconnecting routers
- Checking connectivity
- Forwarding packets
- Finding alternate paths using BFS
- Maintaining packet statistics
- Storing completed packets
- Searching packet history
- Displaying network topology
- Displaying network status

---

## Packet Forwarding Flow

```text
Create Packet
      |
      v
Select Router
      |
      v
Add Packet to Priority Queue
      |
      v
Find Route
      |
      v
Longest Prefix Matching
      |
      v
Check Next Hop
      |
      +----------------------+
      |                      |
   Available             Unavailable
      |                      |
      v                      v
 Forward Packet             BFS
      |                      |
      |                Find Alternate Path
      |                      |
      +----------+-----------+
                 |
                 v
            Update TTL
                 |
                 v
          Update History
                 |
                 v
        Destination Reached?
                 |
          +------+------+
          |             |
         Yes            No
          |             |
          v             v
       Process       Continue
       Packet        Forwarding
```

---

## Example Network Topology

The simulator can represent a topology such as:

```text
        R1
       /  \
      /    \
     R2    R4
      \    /
       \  /
        R3
```

Example connections:

```text
R1 <-> R2
R2 <-> R3
R1 <-> R4
R4 <-> R3
```

This topology can be used to test normal forwarding and alternate-path recovery.

---

## Example Failure Recovery

Suppose the normal path is:

```text
R2 -> R3
```

and the connection between R2 and R3 is disconnected.

The simulator searches for another path and may find:

```text
R2 -> R1 -> R4 -> R3
```

The packet is then forwarded through each router.

Example output:

```text
Next hop is unavailable.
Searching for alternate path...
Alternate path found: R2 -> R1 -> R4 -> R3
Packet forwarded: Router 2 -> Router 1
Packet forwarded: Router 1 -> Router 4
Packet forwarded: Router 4 -> Router 3
Packet has reached its destination!
```

---

## Main Menu

The simulator uses a menu-driven interface:

```text
========== Network Packet Simulator ==========

1. Add Packet
2. Process Packet
3. Display Front Packet
4. Queue Size
5. Packet Statistics
6. Forward Packet
7. Network Status
8. Display Routing Tables
9. Packet History
10. Add Route
11. Remove Route
12. Display Network Topology
13. Disconnect Routers
14. Exit
```

---

## Complexity Analysis

| Operation | Complexity |
|---|---:|
| Add packet | O(log n) |
| Process packet | O(log n) |
| Display front packet | O(1) |
| Queue size | O(1) |
| Find route | O(R) |
| CIDR matching | O(1) per route |
| Add route | O(R) |
| Remove route | O(R) |
| BFS - standard graph analysis | O(V + E) |
| BFS - implementation level | Up to O(VE) |
| Packet history search | Approximately O(n log n) |

Where:

- `n` = number of packets
- `R` = number of routing entries
- `V` = number of routers
- `E` = number of network connections

---

## Testing

The final program was tested using a regression test suite.

The following cases were checked:

- Packet creation
- Packet insertion
- Priority queue ordering
- Packet processing
- Front packet display
- Queue size
- Queue capacity
- Normal packet forwarding
- CIDR matching
- Longest Prefix Matching
- Default route
- Route addition
- Route removal
- Routing table display
- Packet history
- TTL handling
- Router connection
- Router disconnection
- BFS alternate-path recovery
- No alternate path
- Network status
- Network topology
- Network statistics
- Invalid input
- Program exit

### Test Result

All final regression tests passed successfully.

---

## Screenshots

The repository contains screenshots of the important test cases.

The screenshots include:

- Main menu
- Normal packet forwarding
- Longest Prefix Matching
- Routing table
- BFS alternate-path recovery

They are available in the `screenshots` folder.

---

## Project Structure

```text
Network-Packet-Simulator/
│
├── NetworkPacketSimulator.cpp
│
├── README.md
│
├── documentation/
│   └── Network_Packet_Simulator_Project_Report.docx
│
└── screenshots/
    ├── main-menu.png
    ├── normal-forwarding.png
    ├── lpm-routing.png
    ├── routing-table.png
    ├── bfs-recovery-setup.png
    └── bfs-recovery-result.png
```

---

## How to Compile

The project can be compiled using `g++`.

```bash
g++ NetworkPacketSimulator.cpp -o NetworkPacketSimulator
```

### Windows

```bash
NetworkPacketSimulator.exe
```

### Linux / macOS

```bash
./NetworkPacketSimulator
```

---

## Technologies Used

- C++
- Standard C++ Library
- Object-Oriented Programming
- Data Structures
- Computer Networking Concepts
- Git
- GitHub
- Command Line Interface

---

## Learning Outcomes

This project provided practical experience with:

- Priority queues
- Vectors
- Queues
- Maps
- Graph representation
- Breadth First Search
- CIDR addressing
- Longest Prefix Matching
- Routing tables
- Packet forwarding
- TTL management
- Network failure recovery
- Input validation
- Object-oriented programming
- Git and GitHub

---

## Future Improvements

Some possible improvements are:

- Add a graphical interface for the network
- Support larger and configurable network topologies
- Add weighted shortest-path routing
- Simulate packet delay and latency
- Simulate packet loss
- Add bandwidth limitations
- Add more advanced routing protocols
- Save network statistics to external files
- Add persistent logging
- Separate the project into header and source files

---

## Documentation

A detailed project report is available in the `documentation` folder.

The report contains:

- Abstract
- Problem Statement
- Objectives
- System Architecture
- Module Description
- Data Structures
- Algorithms
- Complexity Analysis
- Testing
- Conclusion
- Future Enhancements

---

## Project Information

**Project:** Network Packet Simulator

**Language:** C++

**Domain:** Data Structures and Computer Networking

**Interface:** Command Line

**Version Control:** Git

**Repository:** GitHub

**Status:** Completed and Tested
