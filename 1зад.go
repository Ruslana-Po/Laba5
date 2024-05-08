package main

import (
	"fmt"
	"strings"
)

func examination(product map[string][]string, number string, s string) int {
	k := 0
	for key, value := range product {
		if key == number {
			for _, j := range value {
				if j == s {
					k++
					value=value
				}
			}
		}
	}
	return k
}

func out(product map[string][]string, number string) {
	for key, value := range product {
		if key == number {
			fmt.Print(key, " : ")
			for _, j := range value {
				fmt.Print(j, " ")
			}
			fmt.Println()
		}
	}
}

func main() {
	product := make(map[string][]string)
	for i := 0; i < 2; i++ {
		zone := ""
		if i == 0 {
			zone = "A"
		} else if i == 1 {
			zone = "B"
		}
		for j := 0; j < 19; j++ {
			rack := fmt.Sprintf("%02d", j+1)
			for z := 0; z < 4; z++ {
				sections := fmt.Sprintf("%d", z+1)
				for y := 0; y < 8; y++ {
					shelves := fmt.Sprintf("%d", y+1)
					all := zone + rack + sections + shelves
					for w := 0; w < 10; w++ {
						product[all] = append(product[all], "0")
					}
				}
			}
		}
	}
	var command string
	for {
		fmt.Print("Enter command (ADD/REMOVE/INFO): ")
		fmt.Scanln(&command)
		var merchandise, number string
		var kol int
		if command == "ADD" {
			fmt.Print("Enter merchandise: ")
			fmt.Scanln(&merchandise)
			fmt.Print("Enter quantity: ")
			fmt.Scanln(&kol)
			fmt.Print("Enter address: ")
			fmt.Scanln(&number)
			there := examination(product, number, "0")
			if kol <= 10 && kol <= there {
				k := 0
				for w := 0; w < 10; w++ {
					if product[number][w] == "0" && k < kol {
						product[number][w] = merchandise
						k++
					}
				}
			} else {
				fmt.Println("Not enough space")
			}
		} else if command == "REMOVE" {
			fmt.Print("Enter merchandise: ")
			fmt.Scanln(&merchandise)
			fmt.Print("Enter quantity: ")
			fmt.Scanln(&kol)
			fmt.Print("Enter address: ")
			fmt.Scanln(&number)
			there := examination(product, number, merchandise)
			if kol <= 10 && kol <= there {
				k := 0
				for w := 9; w >= 0; w-- {
					if product[number][w] == merchandise && k < kol {
						product[number][w] = "0"
						k++
					}
				}
			} else {
				fmt.Println("Not enough merchandise")
			}
		} else if command == "INFO" {
			var noEmpty, empty []string
			kolNull := 0
			nullA := 0
			nullB := 0
			for key, value := range product {
			    value=value
				there := examination(product, key, "0")
				kolNull += there
				if strings.HasPrefix(key, "A") {
					nullA += there
				} else {
					nullB += there
				}
				if there < 10 {
					noEmpty = append(noEmpty, key)
				} else {
					empty = append(empty, key)
				}
			}
			fmt.Println("Content of each cell:")
			for _, i := range noEmpty {
				out(product, i)
			}
			fmt.Printf("Warehouse loaded at %.2f %%\n", float64(12160-kolNull)/121.60)
			fmt.Printf("Zone A loaded at %.2f %%\n", float64(6080-nullA)/60.80)
			fmt.Printf("Zone B loaded at %.2f %%\n", float64(6080-nullB)/60.80)
			fmt.Println("Empty cells:")
			for _, i := range empty {
				fmt.Print(i, " ")
			}
			fmt.Println()
		}
	}
}
