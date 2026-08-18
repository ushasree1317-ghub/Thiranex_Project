# Flowchart — Student Management System

## Main Program Flow

```
                         START
                           │
                           ▼
                    ┌─────────────┐
                    │  MAIN MENU  │
                    │             │
                    │ 1. Add      │
                    │ 2. Display  │
                    │ 3. Search   │
                    │ 4. Update   │
                    │ 5. Delete   │
                    │ 6. Exit     │
                    └──────┬──────┘
                           │
                           ▼
                   Read choice
                           │
                           ▼
                 ┌─────────────────┐
                 │  Is choice valid?│
                 └────────┬────────┘
                          │
                   ┌──────┴──────┐
                   │ No          │ Yes
                   ▼             ▼
            ┌──────────┐  ┌──────────────┐
            │ Display  │  │  switch-case │
            │  error   │  └──────┬───────┘
            └────┬─────┘         │
                 │          ┌────┼────┬────┬────┬────┐
                 │          │    │    │    │    │    │
                 │          ▼    ▼    ▼    ▼    ▼    ▼
                 │      ┌────┐┌────┐┌────┐┌────┐┌────┐┌─────┐
                 │      │Add ││Disp││Srch││Upd ││Del ││Exit │
                 │      └─┬──┘└─┬──┘└─┬──┘└─┬──┘└─┬──┘└──┬──┘
                 │        │     │     │     │     │      │
                 │        └─────┴─────┴─────┴─────┘      │
                 │                    │                  │
                 │                    ▼                  │
                 │           ┌────────────────┐          │
                 │           │  Pause screen  │          │
                 │           │  (Press Enter) │          │
                 │           └───────┬────────┘          │
                 │                   │                   │
                 └───────────────────┘                   │
                                                   │
                                                   ▼
                                           ┌─────────────┐
                                           │    END      │
                                           └─────────────┘
```

## Add Student Flow

```
         START
           │
           ▼
    ┌──────────────┐
    │  Read ID     │
    └──────┬───────┘
           │
           ▼
    ┌──────────────┐     Yes
    │ ID exists?   ├──────────► Display error
    └──────┬───────┘              │
           │ No                   │
           ▼                      │
    ┌──────────────┐              │
    │ Read Name    │              │
    │ Read Age     │              │
    │ Read Gender  │              │
    │ Read Course  │              │
    │ Read Phone   │              │
    │ Read Marks   │              │
    └──────┬───────┘              │
           │                      │
           ▼                      │
    ┌──────────────┐              │
    │ Validate all │              │
    │  inputs      │              │
    └──────┬───────┘              │
           │                      │
     ┌─────┴──────┐               │
     │ Invalid?   ├──────► Re-prompt field
     └─────┬──────┘
           │ All valid
           ▼
    ┌──────────────┐
    │ Write record │
    │ to file      │
    └──────┬───────┘
           │
           ▼
    ┌──────────────┐
    │ Display      │
    │ SUCCESS      │
    └──────┬───────┘
           │
           ▼
          END
```

## Delete Student Flow

```
         START
           │
           ▼
    ┌──────────────┐
    │  Read ID     │
    └──────┬───────┘
           │
           ▼
    ┌──────────────┐     No
    │ ID exists?   ├──────────► Display "not found"
    └──────┬───────┘              │
           │ Yes                  │
           ▼                      │
    ┌──────────────┐              │
    │ Display ID   │              │
    │ and Name     │              │
    └──────┬───────┘              │
           │                      │
           ▼                      │
    ┌──────────────┐              │
    │ Confirm (Y/N)│              │
    └──────┬───────┘              │
           │                      │
     ┌─────┴──────┐               │
     │   N / n    │    Y / y      │
     ▼            ▼               │
  Cancel      ┌────────┐          │
  operation   │ Copy   │          │
  │           │ records│          │
  │           │ to     │          │
  │           │ temp   │          │
  │           │ (skip  │          │
  │           │ target)│          │
  │           └───┬────┘          │
  │               │               │
  │               ▼               │
  │           ┌────────┐          │
  │           │Replace │          │
  │           │original│          │
  │           │with    │          │
  │           │temp    │          │
  │           └───┬────┘          │
  │               │               │
  │               ▼               │
  │           ┌────────┐          │
  │           │Display │          │
  │           │SUCCESS │          │
  │           └───┬────┘          │
  │               │               │
  └───────┬───────┘               │
          │                       │
          ▼                       │
         END                      │
```
