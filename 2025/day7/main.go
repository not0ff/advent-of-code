package main

import (
	"bufio"
	"flag"
	"fmt"
	"os"
	"slices"
	"strings"
)

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
	splits := 0
	beams := make([]int, 0)
	for s.Scan() {
		t := strings.Split(s.Text(), "")
		if slices.Contains(t, "S") {
			beams = append(beams, slices.Index(t, "S"))
			continue
		}

		nBeams := make([]int, 0)
		for _, loc := range beams {
			if t[loc] == "^" {
				if !slices.Contains(nBeams, loc-1) {
					nBeams = append(nBeams, loc-1)
				}
				if !slices.Contains(nBeams, loc+1) {
					nBeams = append(nBeams, loc+1)
				}

				t[loc-1] = "|"
				t[loc+1] = "|"
				splits++
			} else {
				if !slices.Contains(nBeams, loc) {
					nBeams = append(nBeams, loc)
				}
				t[loc] = "|"
			}
		}
		// fmt.Print(splits)
		beams = nBeams
		// fmt.Println(t)
		// fmt.Println(nBeams)
	}
	fmt.Println(splits)
}
