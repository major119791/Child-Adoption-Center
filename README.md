# 👶 Child Adoption Center Management System

A desktop terminal application written in **C** that streamlines and manages the operations of a **Child Adoption Center**. Designed as a **Data Structures** project, it leverages structured objects, custom pointers, and persistent file handlings (`.txt` relational simulation) to securely route applications, safely track matching child metadata, and establish two-way asynchronous notification tracking and interactive messaging blocks between Users and Administrators.

---

## 🚀 Key Features

### 👤 User (Prospective Parent) Dashboard
* **Secure Authentication:** Sign up (must be $\ge 21$ years old) and login with masked star (`*`) input password security.
* **Pre-eligibility Application:** Submit verified socioeconomic, criminal-clearance, and residential background forms required before any profiling rights open.
* **Smart Filtering & Searching:** Query available child lists dynamically using filters for **Blood Type**, **Age**, or **Gender**.
* **Adoption Queue Requests:** Submit standard formal match requests tracking directly to admin notification tables.
* **Live Communications Panel:** Asynchronous messaging to check notifications from administrative evaluation changes or text chats with `admin@system.com`.

### 👑 Administrative Panel
* **Child Profile Inventory Management (CRUD):** * Add deep profiles containing unique IDs automatically formatted by target genders ($M/F$ dynamic key tags), age, metrics, blood groupings, and history.
  * Update, view, and wipe entries.
* **Relational Multi-Stage Queue Screening:**
  * **Stage 1 (Application Review):** Process parent profiles from `Pending` status to `Approved` or `Denied`.
  * **Stage 2 (Adoption Request Review):** Link approved profiles with target child files, auto-routing processed children permanently to `adopted_children.txt` logs.
* **Interactive Chat Hub:** View a register of system users, audit backgrounds via linked records, and open dedicated message forms to direct communication logs.

---

## 🛠️ Data Architectures & Schema Design

The system maps data elements using strict native `struct` definitions, optimized memory spaces, and linear dynamic references to replicate real-world entity models.

### 1. Structure Maps
```c
// Tracks demographic background metrics and dynamic memory navigation
typedef struct {
    char email[100];
    char password[100];
    char firstName[50];
    char lastName[50];
    int age;
    char address[100];
    char occupation[50];
    float salary; 
    char phone[15];
    char maritalStatus[20];
    int householdSize;
    char criminalRecord[10];     
    char housingStatus[10];     
    char hasChildren[10];       
    char reason[200];           
    char status[20];
    struct User *next; // Linked Node Pointer          
} User;

// Tracks detailed physical profiles and personal identification codes
typedef struct {
    char id[8]; // Automatically calculated custom code Key
    char name[50];
    char gender[10];
    char birthDate[20];
    int age;
    float height;
    float weight;
    int adopted; // Status Flag Flag (0 = No, 1 = Yes)
    char bloodType[5];
    char allergies[100];
    char medicalConditions[200];
    char educationLevel[50];
    char hobbies[100];
    char languagesSpoken[100];
} Child;
