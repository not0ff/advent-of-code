package main

import (
	"bufio"
	"flag"
	"fmt"
	"os"
	"slices"
	"strconv"
	"strings"
)

func largestInSequence(length int, nums []string) int {
	seq := append([]string{}, nums...)
	gaps := len(seq) - length
	for range gaps {
		min := len(seq) - 1
		for i, v := range seq[:len(seq)-1] {
			if v < seq[i+1] {
				min = i
				break
			}
		}
		seq = slices.Delete(seq, min, min+1)
	}
	r, _ := strconv.Atoi(strings.Join(seq, ""))
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

	totalP1, totalP2 := 0, 0
	s := bufio.NewScanner(f)
	for s.Scan() {
		nums := strings.Split(s.Text(), "")
		totalP1 += largestInSequence(2, nums)
		totalP2 += largestInSequence(12, nums)
	}
	fmt.Printf("Part 1: %v\nPart 2:%v\n", totalP1, totalP2)
}
