package main

import (
	"bufio"
	"flag"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func moveDial(val int, dis int, dir int) (int, int) {
	zeros := 0
	for range dis {
		val += dir
		if val > 99 {
			val = 0
		} else if val < 0 {
			val = 99
		}
		if val == 0 {
			zeros++
		}
	}
	return val, zeros
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

	zerosLeft, allZeros, val := 0, 0, 50
	for s.Scan() {
		seq := strings.Split(s.Text(), "")
		dis, _ := strconv.Atoi(strings.Join(seq[1:], ""))
		var inc int
		switch seq[0] {
		case "L":
			val, inc = moveDial(val, dis, -1)
		case "R":
			val, inc = moveDial(val, dis, 1)
		}
		if val == 0 {
			zerosLeft++
		}
		allZeros += inc
	}
	fmt.Printf("Part 1: %v\nPart 2: %v\n", zerosLeft, allZeros)
}
