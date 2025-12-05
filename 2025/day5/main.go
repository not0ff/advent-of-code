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

type rangeArr struct {
	r [][2]int
}

// Inserts range into a sorted array
func (r *rangeArr) addRange(s, e int) {
	for i, rng := range r.r {
		if rng[0] >= s {
			r.r = slices.Insert(r.r, i, [2]int{s, e})
			return
		}
	}
	r.r = append(r.r, [2]int{s, e})
}

// Merges overlapping ranges together
func (r *rangeArr) mergeRanges() {
	merged := [][2]int{r.r[0]}
	for _, rng := range r.r[1:] {
		prev := &merged[len(merged)-1]
		if rng[0] <= prev[1] {
			if rng[1] > prev[1] {
				prev[1] = rng[1]
			}
		} else {
			merged = append(merged, rng)
			prev = &rng
		}
	}
	r.r = merged
}

// Count all ids in between ranges
func (r *rangeArr) countIds() int {
	c := 0
	for _, rng := range r.r {
		if rng != [2]int{} {
			c += rng[1] - rng[0] + 1
		}
	}
	return c
}

// Check if value is in any of the ranges
func (r *rangeArr) inRange(n int) bool {
	for _, rng := range r.r {
		if n >= rng[0] && n <= rng[1] {
			return true
		}
	}
	return false
}

func getIds(r string) (int, int) {
	t := strings.Split(r, "-")
	s, _ := strconv.Atoi(t[0])
	e, _ := strconv.Atoi(t[1])
	return s, e
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

	r := rangeArr{}
	s := bufio.NewScanner(f)
	for s.Scan() {
		t := s.Text()
		if len(t) == 0 {
			break
		}
		r.addRange(getIds(t))
	}
	r.mergeRanges()

	fresh := 0
	for s.Scan() {
		id, _ := strconv.Atoi(s.Text())
		if r.inRange(id) {
			fresh++
		}
	}

	fmt.Println("Fresh:", fresh)
	fmt.Println("Fresh ids:", r.countIds())
}
