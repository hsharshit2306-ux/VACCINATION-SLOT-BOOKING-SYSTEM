# VACCINATION-SLOT-BOOKING-SYSTEM
💉 Vaccination Slot Booking System (C++ DSA Edition)No chaos. No double-bookings. Just pure Data Structures keeping the line moving! 🚀A menu-driven C++ console application that simulates a real-world vaccination center using Arrays, Hashing (Linear Probing), Circular Queues, and Linked-List Queues—all built completely from scratch without STL shortcuts.✨ Key Features⚡ Instant Citizen Lookup: Register citizens and verify eligibility in $O(1)$ average time.🛡️ Duplicate Prevention: Automatically catches duplicate Citizen IDs and stops double-booking before it happens.🗓️ Real-Time Slot Tracking: Fixed daily time windows with live remaining capacity counters.🔄 Smart Booth Management: Active vaccination booth uses a Circular Queue to recycle freed seats without wasting memory.⏳ Fair Overflow Waitlist: When slots or the booth fill up, citizens join a dynamic FIFO Linked-List Queue.🤖 Auto-Promotion Magic: The moment someone gets vaccinated and leaves the booth, the next person on the waitlist is automatically promoted!🧠 Under the Hood: DSA ArchitectureEvery part of the vaccination center maps to a classic 3rd-semester Data Structure:🧱 Data Structure💻 Module / Class🎯 Real-World Role⏱️ Time ComplexityArraySlot slots[4]Stores fixed daily hourly time slots & capacities$O(1)$ direct accessHashing (Linear Probing)CitizenHashTableCitizen registry (TABLE_SIZE = 101) & duplicate check$O(1)$ avg / $O(n)$ worstCircular QueueCircularQueueActive vaccination booth (capacity 5) with wrap-around$O(1)$ enqueue & dequeueLinear Queue (Linked List)WaitlistQueueUnbounded overflow waitlist ensuring strict FIFO fairness$O(1)$ enqueue & dequeue🔀 System Workflow👤 Citizen Arrives
       │
       ▼
🔑 CitizenHashTable (id % 101) ──▶ Rejects duplicates / unverified IDs
       │
       ▼
📅 Slots Array (Slots 1–4) ──▶ Checks remaining capacity
       │
       ├── [Slot & Booth Available] ──▶ 🔄 CircularQueue (Active Booth)
       │                                         │
       │                                  💉 Vaccinated!
       │                                         │
       └── [Slot or Booth Full] ──────▶ ⏳ WaitlistQueue (FIFO Linked List)
                                                 │
                                    🤖 Auto-Promoted when a booth seat opens!
💡 Interesting Facts & CS Trivia1. Why is TABLE_SIZE = 101 instead of 100? 🔢Choosing a prime number for a hash table size dramatically reduces clustering and collisions. If citizen IDs follow a pattern (like all even numbers or multiples of 10), dividing by 100 leaves half the table empty—whereas dividing by 101 spreads keys evenly across every bucket!2. The "False Overflow" Problem Circular Queues Solved 🔄In a standard array queue, once rear hits the end of the array, you can't add anyone else—even if everyone in front has already been vaccinated and the array is empty! By using modulo wrap-around—$\text{rear} = (\text{rear} + 1) \bmod \text{capacity}$—a Circular Queue turns a straight line into a ring. The exact same trick powers CPU task schedulers, audio streaming buffers, and traffic light controllers!3. Queuing Theory Started in 1909 📞The math behind FIFO waiting lines was invented by Danish mathematician Agner Krarup Erlang while figuring out how many telephone operators Copenhagen needed. Today, the exact same queuing logic manages hospital ERs, airport runways, and large-scale vaccination drives like India's CoWIN platform!4. Why Use a Linked List for the Waitlist? 🔗Unlike the physical booth (which only has a fixed number of chairs), you never know how many people might show up during a sudden rush. A linked-list queue grows dynamically on the heap and frees memory with delete the moment a citizen is served.🚀 Getting StartedPrerequisitesAny C++ compiler supporting C++11 or later (g++, MinGW, or Clang)Terminal / Command Prompt / VS CodeCompile & Run# 1. Clone the repository
git clone https://github.com/your-username/vaccination-slot-booking-dsa.git
cd vaccination-slot-booking-dsa

# 2. Compile the source code
g++ vaccination_booking.cpp -o vaccination_booking

# 3. Run the application
./vaccination_booking        # Linux / macOS
vaccination_booking.exe      # Windows
🖥️ Sample Terminal Preview====== VACCINATION SLOT BOOKING SYSTEM ======
1. Register Citizen (Hashing)
2. View Available Slots (Array)
3. Book Slot / Join Queue (Circular Queue & Waitlist)
4. Process Next Vaccination (Dequeue)
5. Check Citizen Status (Hash Lookup)
6. Display Booth Queue & Waitlist
0. Exit
Enter choice: 3
Enter Citizen ID: 1001
Select Slot ID (1-4): 1
Confirmed! Aarav Sharma added to Active Booth Queue for Slot 1.
🗺️ Future Roadmap[ ] 💾 Persistent Storage: Save and load citizen records using C++ File Handling (.csv / binary files).[ ] 🏆 Priority Queue (Max-Heap): Automatically prioritize senior citizens (age $60+$) and frontline healthcare workers.[ ] 🏥 Multi-Booth Load Balancing: Run an array of Circular Queues to simulate multiple parallel vaccination counters.[ ] 📈 Dynamic Rehashing: Automatically double and rehash the table when the load factor exceeds $0.7$.[ ] 🎨 GUI Upgrade: Build a desktop or web frontend on top of the C++ engine.🎓 Academic DetailsProject: Vaccination Slot Booking SystemSubject: Data Structures and Algorithms (3rd Semester)Institution: School of Computer Science and Engineering, Rungta International Skills University, Bhilai (CG)Author: [Your Full Name] ([Your ERP ID])⭐ If you found this DSA project helpful for learning how queues and hashing work together in real life, give this repo a star!
