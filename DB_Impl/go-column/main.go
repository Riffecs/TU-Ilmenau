package main

import (
	"ColumnStore/core"
	"math/rand"
)

func RandomString(n int) string {
	var letters = []rune("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789")

	s := make([]rune, n)
	for i := range s {
		s[i] = letters[rand.Intn(len(letters))]
	}
	return string(s)
}
func main() {
	/*rand.Seed(time.Now().UnixNano())
	runs := 10000000
	var count [30]int
	for i := 0; i < runs; i++ {
		e := core.Hash(RandomString(rand.Intn(98)+2), 30)
		count[e]++
	}

	for i := 0; i < len(count); i++ {
		fmt.Printf("%.3f\n", float64(count[i])/float64(runs))
	}*/
	var cs = new(core.ColumnStore)

	var atts = []core.AttrInfo{
		{Name: "id", Type: core.INT, Enc: core.NOCOMP},
		{Name: "Name", Type: core.STRING, Enc: core.NOCOMP},
	}

	cs.CreateRelation("students", atts)
	cs.CreateRelation("jobs", atts)

	var rs = cs.Relations["students"].Scan(atts[0:2])
	rs.Load("exampleCSV.csv", ',')
	rs.Print()
	println(rs.Size())
	cs.Relations["students"] = rs

	var rs2 = cs.Relations["jobs"].Scan(atts[0:2])
	rs2.Load("exampleCSV2.csv", ',')
	rs2.Print()
	cs.Relations["jobs"] = rs2
	rs = cs.NestedLoopJoin("students", core.AttrInfo{
		Name: "Studiengang",
		Type: 0,
		Enc:  0,
	}, "jobs", core.AttrInfo{
		Name: "Studiengang",
		Type: 0,
		Enc:  0,
	}, core.EQ)
	rs.Print()

	rs = cs.HashJoin("students", core.AttrInfo{
		Name: "Studiengang",
		Type: 0,
		Enc:  0,
	}, "jobs", core.AttrInfo{
		Name: "Studiengang",
		Type: 0,
		Enc:  0,
	}, core.EQ)
	rs.Print()
}
