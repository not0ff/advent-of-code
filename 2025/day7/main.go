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

	var manifold [][]string
	s := bufio.NewScanner(f)
	for s.Scan() {
		manifold = append(manifold, strings.Split(s.Text(), ""))
	}

	beams := make([]int, len(manifold[0]))
	beams[slices.Index(manifold[0], "S")] = 1
	splits := 0
	for _, layer := range manifold {
		for i, v := range beams {
			if v == 0 {
				continue
			} else if layer[i] == "^" {
				splits++
				beams[i-1] += v
				beams[i+1] += v
				beams[i] = 0

				layer[i-1], layer[i+1] = "|", "|"
			} else {
				layer[i] = "|"
			}
		}
		fmt.Println(layer)
	}

	timelines := 0
	for _, v := range beams {
		timelines += v
	}

	fmt.Printf("Splits: %v Timelines: %v\n", splits, timelines)
}
