package main

import (
	"bufio"
	"flag"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func applyOperators(nums [][]int, ops []string) []int {
	res := make([]int, 0, len(nums))
	for i, op := range ops {
		for _, n := range nums[i] {
			switch op {
			case "+":
				if len(res)-1 < i {
					res = append(res, 0)
				}
				res[i] += n
			case "*":
				if len(res)-1 < i {
					res = append(res, 1)
				}
				res[i] *= n
			}
		}
	}
	return res
}

var InputFile = flag.String("input", "inputs/input.txt", "")

func main() {
	flag.Parse()
	f, err := os.Open(*InputFile)
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	defer f.Close()

	s := bufio.NewScanner(f)
	numsArr := make([][]int, 0)
	res := make([]int, 0)
	for i := 0; s.Scan(); i++ {
		t := s.Text()
		if strings.ContainsAny(t, "+*") {
			res = applyOperators(numsArr, strings.Fields(t))
			break
		}

		for j, n := range strings.Fields(t) {
			if len(numsArr)-1 < j {
				numsArr = append(numsArr, make([]int, 0))
			}
			num, _ := strconv.Atoi(n)
			numsArr[j] = append(numsArr[j], num)
		}
	}

	sum := 0
	for _, n := range res {
		sum += n
	}
	fmt.Println("Answer:", sum)
}
