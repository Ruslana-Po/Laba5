
package main

import (
	"fmt"
	"sort"
)

func main() {
	student := []string{"Мокрушин", "Потапова", "Юдина", "Полевой", "Тарасенко"}
	deduction := []string{}
	inviolable := []string{}

	for {
		var command string
		fmt.Print("Enter command (NEW_STUDENTS/SUSPICIOUS/IMMORTAL/TOP-LIST/SCOUNT): ")
		fmt.Scan(&command)

		switch command {
		case "NEW_STUDENTS":
			var number int
			fmt.Scan(&number)

			if number > 0 {
				for i := 0; i < number; i++ {
					var s string
					fmt.Print("Enter surname: ")
					fmt.Scan(&s)
					student = append(student, s)
				}
				fmt.Printf("Welcome %d clever students!\n", number)
			} else if number < 0 {
				if abs(number) > len(student) {
					fmt.Println("Incorrect")
				} else {
					for i := 0; i > number; i-- {
						student = student[:len(student)-1]
					}
					fmt.Printf("GoodBye %d clever students!\n", abs(number))
				}
			}

		case "SUSPICIOUS":
			var numberStudent int
			fmt.Scan(&numberStudent)

			if numberStudent > 0 && numberStudent <= len(student) {
				found := false
				for _, s := range inviolable {
					if s == student[numberStudent-1] {
						found = true
						break
					}
				}
				if !found {
					deduction = append(deduction, student[numberStudent-1])
					fmt.Printf("The suspected student %d\n", numberStudent)
				} else {
					fmt.Println("Inviolable")
				}
			}

		case "IMMORTAL":
			var numberStudent int
			fmt.Scan(&numberStudent)

			if numberStudent > 0 && numberStudent <= len(student) {
				for i, s := range deduction {
					if s == student[numberStudent-1] {
						deduction = append(deduction[:i], deduction[i+1:]...)
						break
					}
				}
				inviolable = append(inviolable, student[numberStudent-1])
				fmt.Printf("Student %d is immortal!\n", numberStudent)
			}

		case "TOP-LIST":
			fmt.Println("List of students for expulsion:")
			sort.Strings(deduction)
			k := 1
			for _, i := range deduction {
				for j, s := range student {
					if i == s {
						fmt.Printf("Student %d : %s %d\n", k, i, j+1)
						k++
						break
					}
				}
			}

		case "SCOUNT":
			fmt.Printf("List of students for expulsion consists of %d students\n", len(deduction))
		}
	}
}

func abs(x int) int {
	if x < 0 {
		return -x
	}
	return x
}
