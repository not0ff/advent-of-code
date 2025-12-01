package main

import (
	"bufio"
	"flag"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func moveRight(v int, d int) (int, int) {
	zeros := 0
	for range d {
		if v+1 <= 99 {
			v++
		} else {
			v = 0
			zeros++
		}
	}
	return v, zeros
}

func moveLeft(v int, d int) (int, int) {
	zeros := 0
	for range d {
		if v-1 >= 0 {
			v--
			if v == 0 {
				zeros++
			}
		} else {
			v = 99
		}
	}
	return v, zeros
}

func part2(input *bufio.Scanner) string {
	zeros, inc, value := 0, 0, 50
	for input.Scan() {
		seq := strings.Split(input.Text(), "")
		distance, _ := strconv.Atoi(strings.Join(seq[1:], ""))
		switch seq[0] {
		case "L":
			value, inc = moveLeft(value, distance)
		case "R":
			value, inc = moveRight(value, distance)
		}
		zeros += inc
	}
	return fmt.Sprintf("Password: %v", zeros)
}

func part1(input *bufio.Scanner) string {
	count, value := 0, 50
	for input.Scan() {
		seq := strings.Split(input.Text(), "")
		distance, _ := strconv.Atoi(strings.Join(seq[1:], ""))
		switch seq[0] {
		case "L":
			value, _ = moveLeft(value, distance)
		case "R":
			value, _ = moveRight(value, distance)
		}
		if value == 0 {
			count++
		}
	}
	return fmt.Sprintf("Password: %v", count)
}

var (
	Part  = flag.String("part", "p1", "")
	Input = flag.String("input", "inputs/input.txt", "")
)

func main() {
	flag.Parse()
	f, err := os.Open(*Input)
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	defer f.Close()
	s := bufio.NewScanner(f)

	switch *Part {
	case "p1":
		fmt.Println(part1(s))
	case "p2":
		fmt.Println(part2(s))
	}
}
