package main

import (
	"bufio"
	"flag"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func applyOp(res *int, n int, op string) {
	switch op {
	case "+":
		*res += n
	case "*":
		if *res == 0 {
			*res = 1
		}
		*res *= n
	}
}

func part1(lines [][]string) []int {
	nums := make([][]int, 0)
	ops := make([]string, 0)
	for _, l := range lines {
		s := strings.Join(l, "")
		if strings.ContainsAny(s, "+*") {
			ops = strings.Fields(s)
			break
		}

		for i, n := range strings.Fields(s) {
			if len(nums)-1 < i {
				nums = append(nums, make([]int, 0, len(lines)-1))
			}
			num, _ := strconv.Atoi(n)
			nums[i] = append(nums[i], num)
		}
	}
	res := make([]int, len(ops))
	for i, op := range ops {
		for _, n := range nums[i] {
			applyOp(&res[i], n, op)
		}
	}
	return res
}

func part2(lines [][]string) []int {
	// Assumes that lines have equal length
	res := make([]int, 0)
	resN := 0
	var op string
	for i := range lines[0] {
		if s := lines[len(lines)-1][i]; s != " " {
			op = s
		}

		r := ""
		for _, arr := range lines[:len(lines)-1] {
			if arr[i] == " " {
				continue
			}
			r += arr[i]
		}

		if r == "" {
			resN++
			continue
		}

		if len(res)-1 < resN {
			res = append(res, 0)
		}

		n, _ := strconv.Atoi(r)
		applyOp(&res[resN], n, op)
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
	lines := make([][]string, 0)
	for s.Scan() {
		lines = append(lines, strings.Split(s.Text(), ""))
	}

	sum1 := 0
	for _, n := range part1(lines) {
		sum1 += n
	}

	sum2 := 0
	for _, n := range part2(lines) {
		sum2 += n
	}
	fmt.Println("Part 1:", sum1)
	fmt.Println("Part 2:", sum2)
}
