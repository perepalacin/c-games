package main

import (
	"io"
	"os"
	"path/filepath"
)

func check(e error) {
	if e != nil {
		panic(e)
	}
}

type Node struct {
	char     byte
	nextChar *Node
}

func main() {
	pwd, err := os.Getwd()
	check(err)
	path := filepath.Join(pwd, "../pkmn-go/images/moves.html")
	// /Users/perepalacin/Documents/pere-repos/c-game/pkmn-go/images/moves.html
	file, err := os.Open(path)
	check(err)
	defer file.Close()

	var readSize int = 1024
	chunk := make([]byte, readSize)
	for {
		readBlock, err := file.Read(chunk)
		check(err)
		if err == io.EOF {
			break
		}
		if readBlock > 0 {
			parseChunk(chunk)
		}
	}
}

func parseChunk(chunk []byte) {
	var eUtfChar byte = 65
	var eNode Node = Node{char: eUtfChar, nextChar: nil}
	var lUtfChar byte = 108
	var lNode Node = Node{char: lUtfChar, nextChar: &eNode}
	var bUtfChar byte = 98
	var bNode Node = Node{char: bUtfChar, nextChar: &lNode}
	var aUtfChar byte = 97
	var aNode Node = Node{char: aUtfChar, nextChar: &bNode}
	var tUtfChar byte = 116
	var tNode Node = Node{char: tUtfChar, nextChar: &aNode}
	var ltUtfChar byte = 60
	var ltNode Node = Node{char: ltUtfChar, nextChar: &tNode}

	var targetNode = ltNode
	for _, v := range chunk {
		if v != targetNode.char {
			targetNode = ltNode
			continue
		}
		targetNode = *targetNode.nextChar

		if targetNode.nextChar == nil {
			break
		}
	}

	if targetNode.char == eUtfChar {
		// We are in the right chunk
	}
}
