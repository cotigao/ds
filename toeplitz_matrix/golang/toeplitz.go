package main

import "fmt"

func is_toeplitz(arr [][]int) bool {

	height := len(arr)
	width := len(arr[0])

	//sweep the matrix from top-right to bottom-left
	for x := width - 1; x > -1; x-- {
		last := -99999

		//progressively check in right->left direction for every i+1,j+1
		for i, j := x, 0; j < height && i < width; i, j = i+1, j+1 {
			if last == -99999 {
				last = arr[j][i]

			} else if last != arr[j][i] {
				return false

			} else {
				last = arr[j][i]
			}
		}
	}

	return true
}

func main() {
	arr := [][]int{[]int{1, 2, 3, 4}, []int{5, 1, 2, 3}, []int{6, 5, 1, 2}}

	fmt.Println(is_toeplitz(arr))

	arr2 := [][]int{[]int{1, 2, 3, 4}, []int{5, 1, 9, 3}, []int{6, 5, 1, 2}}

	fmt.Println(is_toeplitz(arr2))
}
