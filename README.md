# 🌐 Network Packet Simulator

A C++-based network packet simulation project that combines **Data Structures** with **Computer Networking** concepts to simulate packet scheduling, routing, forwarding, failure recovery, TTL management, and network monitoring.

---

## 📌 Overview

The **Network Packet Simulator** models a network consisting of multiple routers connected through communication links.

Each packet contains information such as:

- Packet Number
- Packet ID
- Source IP Address
- Destination IP Address
- Packet Size
- Priority
- TTL

Packets are stored in router queues and processed according to their priority. Routing decisions are made using **CIDR-based matching and Longest Prefix Matching (LPM)**.

When a configured next-hop router becomes unavailable, the simulator uses **Breadth First Search (BFS)** to discover an alternate path through the available network topology.

The simulator also maintains packet history, routing tables, network topology, and packet statistics.

---

## ✨ Key Features

### 📦 Packet Management

- Create and manage network packets
- Priority-based packet scheduling
- Maximum router queue capacity
- Packet processing and dropping
- Packet history tracking

### 🧭 Routing

- CIDR-based IPv4 matching
- Longest Prefix Matching (LPM)
- Default route support
- Dynamic route addition
- Dynamic route removal

### 🔄 Packet Forwarding

- Router-to-router packet forwarding
- TTL decrementing at every hop
- Destination detection
- Packet processing after reaching destination

### 🚨 Failure Recovery

- Router connection monitoring
- Router disconnection
- BFS-based alternate-path discovery
- Complete alternate-path forwarding
- Prevention of routing loops during recovery
- Handling of situations where no alternate path exists

### 📊 Network Monitoring

- Network topology display
- Router status
- Queue size
- Routing-table display
- Packet statistics
- Active and completed packet history

### 🛡️ Input Validation

- Integer input validation
- Packet field validation
- Router validation
- Prefix-length validation
- Route validation

---

## 🧠 Data Structures Used

| Data Structure | Usage |
|---|---|
| **Priority Queue** | Stores packets according to priority |
| **Vector** | Stores routers, routes, connections, history, and completed packets |
| **Queue** | Used for BFS traversal |
| **Map** | Stores parent relationships during BFS |
| **Graph** | Represents the router network topology |
| **Stringstream** | Used for input and IPv4 parsing |

---

## ⚙️ Algorithms Used

### 1. Priority Queue

Each router maintains a priority queue of packets.

Packets with a higher priority are processed first. If two packets have the same priority, the packet with the smaller packet number is processed first.

### 2. CIDR Matching

The simulator supports CIDR-based network representation such as:

```text
192.168.3.0/24
