# LeetCode Template Usage Guide

## Quick Start

### Method 1: VS Code Snippets (Fastest) ⚡

**Type the alias in any `.cpp` file:**

1. **`lct`** - Full LeetCode template with test cases
2. **`lcs`** - Simple minimal template
3. **`lctest`** - Add a test case block
4. **`pv`** - Print vector snippet
5. **`pv2d`** - Print 2D vector snippet

**How to use:**
1. Open or create a `.cpp` file
2. Type `lct` and press `Tab`
3. Fill in the placeholders (problem ID, name, etc.)
4. Press `Tab` to move to next placeholder

**Example:**
```
Type: lct
Press: Tab
Result: Full template appears with placeholders
```

---

### Method 2: Create New File from Template 🆕

**Option A: Using VS Code Task**
1. Press `Cmd+Shift+P` → "Tasks: Run Task"
2. Select "Create New LeetCode Problem"
3. Enter problem number (e.g., `1`)
4. Enter problem name (e.g., `two-sum`)
5. File created: `1.two-sum.cpp`

**Option B: Using Terminal Script**
```bash
./create_leetcode_problem.sh 1 "two-sum"
# Creates: 1.two-sum.cpp
```

---

## Snippet Aliases Reference

### `lct` - Full Template
Inserts complete LeetCode template with:
- Problem header with LeetCode format
- Includes for common data structures
- Solution class structure
- Test cases framework
- Main function

**Usage:** Type `lct` → `Tab`

---

### `lcs` - Simple Template
Minimal template for quick solutions:
- Basic includes
- Solution class
- Simple main function

**Usage:** Type `lcs` → `Tab`

---

### `lctest` - Test Case Block
Adds a test case block:
```cpp
// Test Case 1
{
    cout << "Test Case 1:" << endl;
    // Add test code
    cout << "✓ Passed" << endl << endl;
}
```

**Usage:** Type `lctest` → `Tab`

---

### `pv` - Print Vector
Quick snippet to print a vector:
```cpp
cout << "[label]: [";
for (size_t i = 0; i < vec.size(); i++) {
    cout << vec[i];
    if (i < vec.size() - 1) cout << ", ";
}
cout << "]" << endl;
```

**Usage:** Type `pv` → `Tab` → Fill placeholders

---

### `pv2d` - Print 2D Vector
Print a 2D vector/matrix:
```cpp
cout << "[label]: [";
for (size_t i = 0; i < vec.size(); i++) {
    cout << "[";
    for (size_t j = 0; j < vec[i].size(); j++) {
        cout << vec[i][j];
        if (j < vec[i].size() - 1) cout << ", ";
    }
    cout << "]";
    if (i < vec.size() - 1) cout << ", ";
}
cout << "]" << endl;
```

**Usage:** Type `pv2d` → `Tab` → Fill placeholders

---

## Complete Workflow Example

### Solving "Two Sum" Problem

**Step 1: Create file**
```bash
# Option A: VS Code Task
Cmd+Shift+P → "Create New LeetCode Problem" → Enter "1" → Enter "two-sum"

# Option B: Script
./create_leetcode_problem.sh 1 "two-sum"
```

**Step 2: Open file and insert template**
1. Open `1.two-sum.cpp`
2. Type `lct` → `Tab`
3. Fill placeholders:
   - Problem ID: `1`
   - Problem Name: `Two Sum`
   - Slug: `two-sum`
   - Difficulty: `Easy`
   - Function: `twoSum`
   - Parameters: `vector<int>& nums, int target`

**Step 3: Implement solution**
```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> map;
        for (int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];
            if (map.find(complement) != map.end()) {
                return {map[complement], i};
            }
            map[nums[i]] = i;
        }
        return {};
    }
};
```

**Step 4: Add test cases**
Type `lctest` → `Tab` → Add test code:
```cpp
// Test Case 1
{
    cout << "Test Case 1:" << endl;
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;
    vector<int> result = sol.twoSum(nums, target);
    pv  // Type this, then Tab, fill: "Output", "result"
    cout << "✓ Passed" << endl << endl;
}
```

**Step 5: Run**
```bash
make 1.two-sum
./1.two-sum

# Or use VS Code: Cmd+Shift+B → "Build and Run"
```

---

## Tips

1. **Use `lct` for new problems** - Full template with everything
2. **Use `lcs` for quick tests** - Minimal boilerplate
3. **Use `lctest` to add more test cases** - Consistent format
4. **Use `pv` and `pv2d` for debugging** - Quick output
5. **Before submitting:** Remove `main()` and test code

---

## Keyboard Shortcuts Summary

| Action | Shortcut |
|--------|---------|
| Insert full template | Type `lct` → `Tab` |
| Insert simple template | Type `lcs` → `Tab` |
| Add test case | Type `lctest` → `Tab` |
| Print vector | Type `pv` → `Tab` |
| Print 2D vector | Type `pv2d` → `Tab` |
| Create new problem | `Cmd+Shift+P` → "Create New LeetCode Problem" |
| Build & Run | `Cmd+Shift+B` → "Build and Run" |

---

## File Structure

```
Leetcode_interesting_repo/
├── .vscode/
│   ├── cpp.code-snippets      # Snippet definitions (aliases)
│   ├── leetcode_template.cpp   # Template file
│   └── tasks.json              # VS Code tasks
├── create_leetcode_problem.sh  # Script to create new files
└── [your problem files].cpp
```

---

## Troubleshooting

**Snippets not working?**
- Make sure you're in a `.cpp` file
- Check that `.vscode/cpp.code-snippets` exists
- Reload VS Code window (`Cmd+Shift+P` → "Developer: Reload Window")

**Task not showing?**
- Check `.vscode/tasks.json` exists
- Try `Cmd+Shift+P` → "Tasks: Run Task" → Look for "Create New LeetCode Problem"

**Script permission denied?**
```bash
chmod +x create_leetcode_problem.sh
```
