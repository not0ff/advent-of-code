package main

func GetLPS(str string) []int {
	lps := make([]int, len(str))
	n, len := len(str), 0
	lps[0] = 0

	for i := 1; i < n; {
		if str[i] == str[len] {
			len++
			lps[i] = len
			i++
		} else {
			if len == 0 {
				lps[i] = 0
				i++
			} else {
				len = lps[len-1]
			}
		}
	}
	return lps
}
