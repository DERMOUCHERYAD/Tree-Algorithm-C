
# Tree-Algorithm-C

This repository contains a series of exercises and test files for implementing tree data structures in C. The exercises focus on building and testing tree operations, including searching, adding species and characteristics, and handling insertion legality.

## Recommendations on the Use of Files for APP3
**Must Read!**

****************************************************************  
### For Everyone  
****************************************************************  

Fill in the names of the members of your team here:

- **Name1 - Firstname1**: DERMOUCHE Mohammed Ryad  
- **Name2 - Firstname2**: DIOP Amsatou  

If you have comments, remarks, etc. for the submission, you can put them here:

For **act5**, I tried to do it but nothing worked, so I deleted it. I had tried several algorithms, but nothing worked.

---

## Work to be Done  
To start **Act I**, implement the search for the number of species and characteristics of a tree. Modify the `arbresphylo.{c,py}` file.

For the following acts, you will also need to modify the main program (`main.{c,py}`) to test your functions.

We provide automated programs to test your functions. For each function in Acts I, II, III, and IV, it is important to respect the required specification to pass the test suites.

### Act IV Notes:
For **Act IV**, it is assumed that:
- It is not possible to insert a characteristic into an empty tree.
- It is not possible to insert a characteristic that is not possessed by any species already present in the tree (in this case, `ajout_espece` does the job).
  
This prevents the addition of characteristic nodes without children, which could be confused with species/leaves.

You are responsible for testing and providing your own tests for **Act V** for submission.

---

## Testing Your C Implementation
You will find files in the `tests/` directory that allow you to test your functions by executing your main program. For example:

```bash
./main tests/arbre-simple.test
```

Run all the tests:

```bash
make tests_acte1
```

Or manually run one of the tests (for example, during debugging of a particular test):

```bash
./acte1 tests_acte1/acte1_arbre-simple.test
```

---

## Description of Test File Formats

### Format for Act I Tests:
- File name of the tree
- Number of species
- Number of characteristics

### Format for Act II Tests:
- File name of the tree
- Name of the species to search
- "present" or "absent" depending on whether the species is present
- If species is present:
  - Number of characteristics
  - The species' characteristics (on a single line, separated by spaces)

### Format for Act III-A Tests:
- File name of the tree
- Name of the species to add
- Number of characteristics of the species to add
- "possible" if the insertion is legal, "impossible" otherwise
- Test series on the tree after insertion:
  - Number of species in the tree
  - Number of characteristics of the tree
  - Number of species to test (may be fewer than the total number of species)
  - For each species:
    - Species name
    - Number of characteristics
    - List of characteristics (on a single line, separated by spaces)

### Format for Act III-B Tests:
- File name of the tree
- List of characteristics at level 1 (on a single line, separated by spaces)
- List of characteristics at level 2
- List of characteristics at level 3

### Format for Act IV Tests:
- File name of the tree
- Name of the characteristic to add
- Number of species possessing this characteristic
- List of species that possess this characteristic
- "possible" if the insertion is legal, "impossible" otherwise
- Test series on the tree after insertion:
  - Number of species in the tree
  - Number of characteristics of the tree
  - Number of species to test (may be fewer than the total number of species)
  - For each species:
    - Species name
    - Number of characteristics
    - List of characteristics (on a single line, separated by spaces)

---

## Running Tests with Example Commands

To run all the tests, you can execute the following command:

```bash
make tests_acte1
```

Alternatively, you can manually run one of the tests, for example:

```bash
./acte1 tests_acte1/acte1_arbre-simple.test
```

Make sure that the files in the `tests/` directory match the formats described above for the specific acts (I, II, III, and IV) to ensure proper test execution.
