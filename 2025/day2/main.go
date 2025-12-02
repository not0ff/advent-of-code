package main

import (
	"flag"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func isRepeating(x int) bool {
	s := strconv.Itoa(x)
	m := len(s) / 2
	l, r := s[:m], s[m:]
	return l == r
}

func getInvalidSum(start int, end int) int {
	sum := 0
	for i := start; i <= end; i++ {
		if isRepeating(i) {
			sum += i
		}
	}
	return sum
}

var InputFile = flag.String("input", "inputs/input.txt", "")

func main() {
	flag.Parse()
	f, err := os.ReadFile(*InputFile)
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}

	sum := 0
	ranges := strings.SplitSeq(string(f), ",")
	for pair := range ranges {
		t := strings.Split(pair, "-")
		first, _ := strconv.Atoi(t[0])
		last, _ := strconv.Atoi(t[1])
		sum += getInvalidSum(first, last)
	}
	fmt.Printf("Sum of invalid: %v\n", sum)
}
