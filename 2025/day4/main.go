package main

import (
	"bufio"
	"flag"
	"fmt"
	"os"
	"time"
)

type Grid struct {
	g [][]int
}

func NewGrid(s *bufio.Scanner) *Grid {
	g := &Grid{g: make([][]int, 0)}

	for i := 0; s.Scan(); i = i + 1 {
		l := s.Text()
		g.g = append(g.g, make([]int, len(l)))
		for j, s := range l {
			if s == '@' {
				g.g[i][j] = 1
			} else {
				g.g[i][j] = 0
			}
		}
	}
	return g
}

// Return value at x y position in a grid
// Returns 0 for out-of-bound position
func (g *Grid) Get(x, y int) int {
	if y > len(g.g)-1 || y < 0 {
		return 0
	}
	if x > len(g.g[y])-1 || x < 0 {
		return 0
	}
	return g.g[y][x]
}

func (g *Grid) String() string {
	s := ""
	for y := range g.g {
		for x := range g.g[y] {
			if g.g[y][x] == 1 {
				s += "@"
			} else {
				s += "."
			}
		}
		s += "\n"
	}
	return s
}

func (g *Grid) CountAccessible(maxNear int) int {
	c := 0
	for y := range g.g {
		for x := range g.g[y] {
			n := g.Get(x-1, y-1) + g.Get(x, y-1) + g.Get(x+1, y-1) + g.Get(x-1, y) + g.Get(x+1, y) + g.Get(x-1, y+1) + g.Get(x, y+1) + g.Get(x+1, y+1)
			if g.Get(x, y) == 1 && n <= maxNear {
				c++
			}
		}
	}
	return c
}

func (g *Grid) CountRemovable(maxNear int) int {
	c := 0
	for true {
		toRemove := [][2]int{}
		for y := range g.g {
			for x := range g.g[y] {
				n := g.Get(x-1, y-1) + g.Get(x, y-1) + g.Get(x+1, y-1) + g.Get(x-1, y) + g.Get(x+1, y) + g.Get(x-1, y+1) + g.Get(x, y+1) + g.Get(x+1, y+1)
				if g.Get(x, y) == 1 && n <= maxNear {
					toRemove = append(toRemove, [2]int{x, y})
					c++
				}
			}
		}
		if len(toRemove) == 0 {
			break
		}
		for _, r := range toRemove {
			x, y := r[0], r[1]
			g.g[y][x] = 0
		}
	}

	return c
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
	grid := NewGrid(s)

	start := time.Now()
	fmt.Printf("Can be accessed: %v ", grid.CountAccessible(3))
	fmt.Printf("Microseconds: %v\n", time.Since(start).Microseconds())

	start = time.Now()
	fmt.Printf("Can be removed: %v ", grid.CountRemovable(3))
	fmt.Printf("Microseconds: %v\n", time.Since(start).Microseconds())
}
