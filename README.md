# PriceWave: Dynamic E-Commerce Pricing & Optimization Engine

## 1. Problem Statement
Modern e-commerce platforms like Amazon handle millions of transactions, fluctuating product demands, and complex promotional stacking concurrently. Managing these operations seamlessly requires backend tracking systems optimized for extreme speed, low latency, and absolute operational data integrity. This project addresses the challenge of building a high-performance text-based simulator capable of processing instantaneous price trackings, rolling back transactional price changes, queueing real-time customer checkouts, evaluating product bundling constraints, and execution of automated strategic discounts.

---

## 2. Objectives
* Design and implement a cohesive console system utilizing core Data Structures and Algorithms (DSA) in C++.
* Attain constant-time complexity $O(1)$ for product record lookup and dynamic inventory modifications.
* Ensure data ordering integrity using sequential structural wrappers (LIFO stacks and FIFO queues).
* Simulate recommendation maps via Adjacency-List Graphs to associate cross-selling opportunities.
* Maximize operational profit and yield optimization via greedy strategy algorithmic rules.

---

## 3. System Overview / Architecture
The architecture operates strictly as an in-memory database configuration managed by an encapsulated central engine (`PriceWaveSystem`). Data inputs map out via structured relationships between individual instances of custom entity blueprints (`struct Product`) and structural collections.

* **Data Layer:** Utilizes Hash Maps for item persistence, Graphs for item dependencies, and Stacks/Queues for active application logic lifecycles.
* **Control Layer:** An interactive iterative process loop (`main` choice controller) parsing commands dynamically without database overhead dependencies.

---

## 4. Data Structures and Algorithms Used
* **Hash Map (`std::unordered_map`):** Implements buckets for instant index key indexing to map individual product records directly via explicit integer Identifiers (`ID`).
* **Stack (`std::stack`):** Manages dynamic structural pairs tracking states of old pricing entries to support transactional rollbacks.
* **Queue (`std::queue`):** Buffers incoming structural integers representing buyer lines to enforce serialized chronological execution.
* **Graph (Adjacency List):** Maps undirected relationship links across related product records to evaluate cross-purchase bundle arrays.
* **Binary Search:** Iteratively segments balanced ranges to execute text target matches over structured arrays.
* **Greedy Strategy:** Evaluates optimal localized discounts sequentially based on mathematical order weight to minimize compound margin leaks.

---

## 5. Implementation Approach
The application is structured completely within a modular, single-translation-unit design using standard C++ libraries to avoid unnecessary overhead and ensure clean, cross-platform execution:
1. **Product Initialization:** Hardcodes an initial batch of 15 diversified consumer items spanning distinct retail categories.
2. **Encapsulated Class Logic:** Isolates independent member procedures for data mutator handling (`updatePrice`), queue tracking (`addToCheckout`), and network exploration (`suggestBundles`).
3. **Decoupled CLI Processing:** Coordinates standard system streaming pipelines (`cin`/`cout`) wrapped seamlessly into controlled system conditional states.

---

## 6. Time and Space Complexity Analysis

| Feature Component | Chosen Underlying Structure / Strategy | Average Time Complexity | Worst-Case Space Complexity |
| :--- | :--- | :--- | :--- |
| Price Tracking & Retrieval | Hash Map Lookup | $O(1)$ | $O(n)$ |
| Flash Sale Price Undo | Stack Rollback Logic | $O(1)$ | $O(m)$ (History Stack Size) |
| Checkout Operations | FIFO Sequence Queue | $O(1)$ | $O(k)$ (Active Queue Size) |
| Barcode Target Lookup | Array Sort + Binary Search | $O(n \log n)$ | $O(n)$ |
| Best Sellers Ranker | Vector Extraction + Sort | $O(n \log n)$ | $O(n)$ |
| Related Product Bundle | Graph Adjacency Iteration | $O(V)$ (Bounded by Max Degree) | $O(V + E)$ |
| Compound Discount Finder | Static Greedy Path Execution | $O(1)$ | $O(1)$ |
| Profit Dynamic Optimizer | Direct Value Modifiers | $O(1)$ | $O(1)$ |

---

## 7. Execution Steps
### Prerequisites
* Ensure a standard C++ compiler environment is present (e.g., `GCC/MinGW` or `Clang`).

### Compilation and Launch Commands
1. Open your native command terminal or integrated development pipeline.
2. Compile the source file using the optimizing layout command:
   ```bash
   g++ main.cpp -o pricewave
3. Initialize the compiled binary layout directly:
Windows Environment: .\pricewave
Unix/macOS Environments: ./pricewave

8. Sample Inputs and Outputs
=== Main Menu Selection ===
Select Option: 10 (Profit Maximizer Engine)
Enter Product ID: 101
Select Demand Level (1: Low, 2: Medium, 3: High): 3

--- Output Frame ---
--- Profit Maximizer Engine ---
Alert: High demand! Implementing 20% surge pricing.
Smartphone Pro dynamically priced at: Rs 18000 (Old Price: Rs 15000)

9. Screenshots of Program Execution

UI Main Interactive Dashboard View

<img width="1465" height="918" alt="Screenshot 2026-06-21 at 6 12 59 PM" src="https://github.com/user-attachments/assets/b6d934ae-d37e-41cf-8c86-ba134fb432d7" />

Barcode Matching Validation (Binary Search Execution)

<img width="1470" height="926" alt="Screenshot 2026-06-21 at 6 14 33 PM" src="https://github.com/user-attachments/assets/a318acbc-304b-4120-a70e-d98a9f71c98c" />

Stack Trigger Verification (Price Undo Operation)

<img width="1470" height="924" alt="Screenshot 2026-06-21 at 6 15 24 PM" src="https://github.com/user-attachments/assets/309d06d6-b9c8-43e3-a7fa-43ed60c77213" />

10. Results and Observations

Instant Database Simulation Lookups: Integrating tracking attributes over an unordered map map index bypasses structural list traversing entirely, proving that an $O(1)$ architecture provides optimal responsiveness for large product catalogs.

Strict Algorithmic Sorting Behavior: Running binary matching requires maintaining sorted vector elements. This explicit sort action impacts isolated performance ($O(n \log n)$ overhead), highlighting the practical design tradeoff between layout sorting costs versus query speeds.

Deterministic Decision Execution: Incorporating greedy stack configurations enforces ordered evaluation mechanics cleanly without processing overhead or system stalling.

11. Conclusion

The PriceWave project provides a comprehensive overview of fundamental back-end operations managed by modern digital storefront applications. By leveraging a structured data model in C++, we proved that combining specialized memory wrappers (such as Stacks, Queues, Maps, and Graphs) creates a highly efficient system that optimizes performance and ensures absolute accuracy across critical platform workflows.

Name: Ashish Shravan Kumar Gupta

Cohort: Jeff Bezos

Roll no.: 150096725084
