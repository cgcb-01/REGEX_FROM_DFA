#  DFA to Regular Expression Converter

![States: DFA](https://img.shields.io/badge/States-yellow?style=flat-square&logo=appveyor&logoColor=black)
![Symbols: Input](https://img.shields.io/badge/Symbols-blue?style=flat-square&logo=typescript&logoColor=white)
![Conversion: DFA→Regex](https://img.shields.io/badge/Conversion-yellow?style=flat-square&logo=regex&logoColor=black)
![Language: C++](https://img.shields.io/badge/Language-C++-blue?style=flat-square&logo=c%2B%2B&logoColor=white)
![Platform: CLI](https://img.shields.io/badge/Platform-CLI-yellow?style=flat-square&logo=gnu-bash&logoColor=black)

---

This C++ project converts a **Deterministic Finite Automaton (DFA)** into its equivalent **Regular Expression (Regex)** using the **state elimination method**.

---

## 📌 Features

- Interactive CLI to input DFA components
- Automatically adds start and final dummy states for proper elimination
- Handles ε (epsilon) transitions
- Supports multiple final states
- Merges multiple transitions between the same states
- Handles and ignores dummy (dead/unreachable) states gracefully
- Simplifies unnecessary parentheses in the final expression

---

## 🚀 How It Works

1. **User Input:**
   - States
   - Start State
   - Final States
   - Transition Symbols
   - Transitions

2. **Processing:**
   - Adds virtual Start (`Start0`) and Final (`Final0`) states
   - Merges transitions between same source and destination
   - Eliminates intermediate states via the state elimination method
   - Generates a Regular Expression using path combinations
   - Simplifies excess brackets in the final expression

3. **Output:**
   - Transition Table
   - Final Regular Expression

---

## 🧪 Sample DFA Input
```
States: 1 2 3 -1
Start State: 1
Final States: 2 3 -1
Symbols: a b -1

Transitions:
For state '1': a -> 2, b -> 3
For state '2': a -> 3, b -> 2
For state '3': a -> 2, b -> 3
```

### ✅ Output:
```
The Regular Expression is: a(b)*U(b(bUa(b)a))

```

## 🛠️ How to Compile & Run

```
g++ -o dfa_to_regex dfa_to_regex.cpp
./dfa_to_regex
```
# 🧠 Important Notes
To stop entering states, final states, or symbols, type -1.

Epsilon (ε) transitions are represented as "E" internally.

Redundant outer parentheses are removed for cleaner output.

# 🧳 Future Improvements
i. GUI support for DFA input

ii. Visual representation of transitions

iii. Support for NFA and Epsilon-NFA to Regex conversion

# 👨‍💻 Author
cgcb-01
🔗 https://github.com/cgcb-01

# 📄 License
This project is licensed under the MIT License.
