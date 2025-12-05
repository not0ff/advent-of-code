package main

import (
	"bufio"
	"flag"
	"fmt"
	"os"
	"strconv"
	"strings"
)

type ruleSet [][2]int

func (r *ruleSet) addRange(s, e int) {
	*r = append(*r, [2]int{s, e})
}

func (r *ruleSet) inRange(n int) bool {
	for _, rng := range *r {
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

	var rules ruleSet
	s := bufio.NewScanner(f)
	for s.Scan() {
		t := s.Text()
		if len(t) == 0 {
			break
		}
		rules.addRange(getIds(t))
	}
	fresh := 0
	for s.Scan() {
		id, _ := strconv.Atoi(s.Text())
		if rules.inRange(id) {
			fresh++
		}
	}

	fmt.Println("Fresh:", fresh)
}
