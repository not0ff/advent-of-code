package main

import (
	"flag"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func repeatedTwice(str string) bool {
	m := len(str) / 2
	return str[:m] == str[m:]
}

func countShortestRepeat(str string) int {
	strLen := len(str)
	for i := 1; i <= strLen; i++ {
		subStr := str[:i]
		subCount := strings.Count(str, subStr)
		if float32(subCount) == float32(strLen)/float32(i) {
			return subCount
		}
	}
	return 1
}

var InputFile = flag.String("input", "inputs/input.txt", "")

func main() {
	flag.Parse()
	f, err := os.ReadFile(*InputFile)
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}

	firstSum, fullSum := 0, 0
	ranges := strings.SplitSeq(string(f), ",")
	for pair := range ranges {
		t := strings.Split(pair, "-")
		first, _ := strconv.Atoi(t[0])
		last, _ := strconv.Atoi(t[1])
		for i := first; i <= last; i++ {
			s := strconv.Itoa(i)
			if repeatedTwice(s) {
				firstSum += i
			}
			if countShortestRepeat(s) >= 2 {
				fullSum += i
			}
		}
	}
	fmt.Printf("First sum: %v\nFull sum: %v\n", firstSum, fullSum)
}
