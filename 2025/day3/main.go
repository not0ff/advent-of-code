package main

import (
	"bufio"
	"flag"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func largestCombination(nums []string) int {
	var a, b string
	for i, tens := range nums[:len(nums)-1] {
		if tens <= a {
			continue
		}

		a, b = tens, nums[i+1]
		for _, units := range nums[i+1:] {
			if units > b {
				b = units
			}
		}
	}
	r, _ := strconv.Atoi(a + b)
	return r
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

	total := 0
	s := bufio.NewScanner(f)
	for s.Scan() {
		nums := strings.Split(s.Text(), "")
		total += largestCombination(nums)
	}
	fmt.Println("Total output:", total)
}
