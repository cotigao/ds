//check if the given matrix is toeplitz

package main

import "fmt"

func is_toeplitz(arr [][]int) bool {
	channel := make(chan bool)

	height := len(arr)
	width := len(arr[0])

	go func() {
		val := true

	outer:
		//sweep the matrix from top-right
		for x := width - 1; x > -1; x-- {
			//progressively check in left->right direction for every i+1,j+1
			for i, j := x, 0; j < height && i < width; i, j = i+1, j+1 {
				if j > 0 && arr[j][i] != arr[j-1][i-1] {
					val = false
					break outer
				}
			}
		}

		channel <- val
	}()

	go func() {
		val := true

	outer:
		//sweep the matrix from bottom-left
		for x := 0; x < width; x++ {
			//progressively check in left->right direction for every i-1,j-1
			for i, j := x, height-1; j > -1 && i > -1; i, j = i-1, j-1 {
				if j < height-1 && arr[j][i] != arr[j+1][i+1] {
					val = false
					break outer
				}
			}
		}

		channel <- val
	}()

	return <-channel && <-channel
}

func main() {
	arr := [][]int{[]int{1, 2, 3, 4}, []int{5, 1, 2, 3}, []int{6, 5, 1, 2}}
	fmt.Println(is_toeplitz(arr))

	arr2 := [][]int{[]int{1, 2, 3, 4}, []int{5, 1, 9, 3}, []int{6, 5, 1, 2}}
	fmt.Println(is_toeplitz(arr2))

	arr3 := [][]int{[]int{1, 2}, []int{3, 1}}
	fmt.Println(is_toeplitz(arr3))

	arr4 := [][]int{[]int{1}, []int{2}}
	fmt.Println(is_toeplitz(arr4))

	arr5 := [][]int{[]int{1}}
	fmt.Println(is_toeplitz(arr5))

	arr6 := [][]int{[]int{1, 2, 3}, []int{5, 1, 2}, []int{3, 6, 1}}
	fmt.Println(is_toeplitz(arr6))
}
