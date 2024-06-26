/*67. Add Binary
Solved
Easy

Topics
Companies
Given two binary strings a and b, return their sum as a binary string.

 

Example 1:

Input: a = "11", b = "1"
Output: "100"
Example 2:

Input: a = "1010", b = "1011"
Output: "10101"
 

Constraints:

1 <= a.length, b.length <= 104
a and b consist only of '0' or '1' characters.
Each string does not contain leading zeros except for the zero itself.*/
package main
import "fmt"
import "strconv"
func addBinary(a string, b string) string {
    carry := 0
    res := ""
    if len(a) == 0 || len(b) == 0 {
        return res
    }
    for i, j := len(a)-1, len(b)-1 ; i >= 0 || j >=0 ; i, j = i-1, j-1  {
            sum:= 0
            if i >= 0 && a[i] == '1' {
                sum = sum + 1
            }
            if j >= 0 && b[j] == '1' {
                sum = sum + 1
            }
            sum+=carry
            if sum == 1 {
                carry = 0
                sum = 1
            } else if sum == 2{
                carry = 1
                sum = 0
            } else if sum == 3 {
                carry = 1
                sum = 1
            }
            res = strconv.Itoa(sum) + res
    }
    if carry > 0 {
        return strconv.Itoa(carry) + res
    } else {
        return res
    }
}
func main() {
	a := "1101"
	b := "11100"
	fmt.Println(addBinary(a, b))
}