package core

import (
	"bufio"
	"errors"
	"os"
	"strconv"
)

/*Load a .csv file into a relation*/
func (r *Relation) Load(csvFile string, separator rune) error {
	//Initialisieren des csv-Files und Scanner
	data, err := os.Open(csvFile)
	if err != nil {
		return err
	}
	r.Columns = nil
	fileScanner := bufio.NewScanner(data)

	fileScanner.Split(bufio.ScanRunes)
	s := ""
	//Initialisieren Ende
	//Beginn einlesen
	for fileScanner.Scan() { //Read the first line, one letter at a time
		if fileScanner.Text() == string(separator) { //end of single argument name
			r.Columns = append(r.Columns, Column{
				Signature: AttrInfo{
					Name: s,
					Type: INT,
					Enc:  NOCOMP,
				},
				Data: new([]string),
			})
			s = ""
			continue
		}
		if fileScanner.Text() == string('\n') { //End of argument line
			r.Columns = append(r.Columns, Column{
				Signature: AttrInfo{
					Name: s,
					Type: INT,
					Enc:  NOCOMP,
				},
				Data: new([]string),
			})
			s = ""
			break
		}
		if fileScanner.Text() == string('\r') { //Windows ends lines with \r \n
			continue
		}
		s += fileScanner.Text()
	}

	currentColumn := 0
	for fileScanner.Scan() { //read the set
		if fileScanner.Text() == string(separator) {
			if currentColumn < len(r.Columns) {
				c := new([]string)
				if r.Columns[currentColumn].Data != nil {
					c = r.Columns[currentColumn].Data.(*[]string)
				}
				*c = append(*c, s)
				r.Columns[currentColumn].Data = c
				r.Columns[currentColumn].Signature.Type = typeCheck(r.Columns[currentColumn].Signature.Type, s)
			}
			s = ""
			currentColumn++
			continue
		}
		if fileScanner.Text() == string('\n') {
			c := new([]string)
			if r.Columns[currentColumn].Data != nil {
				c = r.Columns[currentColumn].Data.(*[]string)
			}
			*c = append(*c, s)
			r.Columns[currentColumn].Data = c
			r.Columns[currentColumn].Signature.Type = typeCheck(r.Columns[currentColumn].Signature.Type, s) //Checks if the current entry matches the previously assumed Datatype
			currentColumn = 0
			s = ""
			continue
		}
		if fileScanner.Text() == string('\r') {
			continue
		}
		s += fileScanner.Text()
	}
	//Adds the final entry
	c := new([]string)
	if r.Columns[currentColumn].Data != nil {
		c = r.Columns[currentColumn].Data.(*[]string)
	}
	*c = append(*c, s)
	r.Columns[currentColumn].Data = c

	r.Name = data.Name()
	err = data.Close()
	if err != nil {
		return err
	}
	return nil
}

func (r *Relation) Scan(colList []AttrInfo) Relationer {
	var rs = new(Relation)
	for i := 0; i < len(r.Columns); i++ {
		for j := 0; j < len(colList); j++ { //Loops through existing and demanded Attributes and adds positiv matches
			if r.Columns[i].Signature.Name == colList[j].Name {
				rs.Columns = append(rs.Columns, r.Columns[i])
				break
			}
		}
	}
	rs.Name = r.Name
	return rs
}

func (r *Relation) Select(colName AttrInfo, comp Comparison, compVal interface{}) (Relationer, error) {
	var rs = new(Relation)
	rs.Name = r.Name
	for i := 0; i < len(r.Columns); i++ {
		rs.Columns = append(rs.Columns, Column{
			Signature: r.Columns[i].Signature,
			Data:      new([]string),
		})
	}
	//Extracts the column under consideration
	c := new([]string)
	dt := STRING
	foundColum := false
	for i := 0; i < len(r.Columns); i++ {
		if colName.Name == r.Columns[i].Signature.Name {
			c = r.Columns[i].Data.(*[]string)
			dt = r.Columns[i].Signature.Type
			foundColum = true
			break
		}
	}
	if !foundColum {
		return rs, errors.New("no such colum")
	}
	/*
		Procedure for all Cases:
		Converts input value to matching type
		Loops over all entry's
			convert entry's into matching data type
			Perform demanded comparison
			adds entry if comparison returns true
	*/
	switch dt { //TODO: Ordntliche Typverwaltung(Verfahen bei falschen datentypen)
	case INT:
		intComp := int64(compVal.(int))
		for i := 0; i < len(*c); i++ {
			val, _ := strconv.ParseInt((*c)[i], 10, 64)
			switch comp {
			case EQ:
				if val == intComp {
					break
				}
				continue
			case NEQ:
				if val != intComp {
					break
				}
				continue
			case LT:
				if val < intComp {
					break
				}
				continue
			case LE:
				if val <= intComp {
					break
				}
				continue
			case GT:
				if val > intComp {
					break
				}
				continue
			case GE:
				if val >= intComp {
					break
				}
				continue
			}
			for j := 0; j < len(rs.Columns); j++ {
				*rs.Columns[j].Data.(*[]string) = append(*rs.Columns[j].Data.(*[]string), (*r.Columns[j].Data.(*[]string))[i])
			}
		}
		break //END INT
	case FLOAT:
		floatComp := float64(compVal.(float64))
		for i := 0; i < len(*c); i++ {
			val, _ := strconv.ParseFloat((*c)[i], 64)
			switch comp {
			case EQ:
				if val == floatComp {
					break
				}
				continue
			case NEQ:
				if val != floatComp {
					break
				}
				continue
			case LT:
				if val < floatComp {
					break
				}
				continue
			case LE:
				if val <= floatComp {
					break
				}
				continue
			case GT:
				if val > floatComp {
					break
				}
				continue
			case GE:
				if val >= floatComp {
					break
				}
				continue
			}
			for j := 0; j < len(rs.Columns); j++ {
				*rs.Columns[j].Data.(*[]string) = append(*rs.Columns[j].Data.(*[]string), (*r.Columns[j].Data.(*[]string))[i])
			}
		}
		break //END FLOAT
	case STRING:
		stringComp := compVal.(string)
		for i := 0; i < len(*c); i++ {
			val := (*c)[i]
			switch comp {
			case EQ:
				if val == stringComp {
					break
				}
				continue
			case NEQ:
				if val != stringComp {
					break
				}
				continue
			case LT:
				if val < stringComp {
					break
				}
				continue
			case LE:
				if val <= stringComp {
					break
				}
				continue
			case GT:
				if val > stringComp {
					break
				}
				continue
			case GE:
				if val >= stringComp {
					break
				}
				continue
			}
			for j := 0; j < len(rs.Columns); j++ {
				*rs.Columns[j].Data.(*[]string) = append(*rs.Columns[j].Data.(*[]string), (*r.Columns[j].Data.(*[]string))[i])
			}
		}
		break //END FLOAT
	}

	return rs, nil
}

func (r *Relation) Print() {
	/*
		Print the name
		Converts the table to [][]string
		Loop over all entries and print then in a nice way
	*/

	println(r.Name)
	if len(r.Columns) == 0 {
		return
	}
	var stringTable [][]string
	var maxLen []int
	for i := 0; i < len(r.Columns); i++ {
		stringTable = append(stringTable, []string{r.Columns[i].Signature.Name})
		maxLen = append(maxLen, len(r.Columns[i].Signature.Name))
		if r.Columns[i].Data != nil {
			currentColum := r.Columns[i].Data.(*[]string)
			for j := 0; j < len(*currentColum); j++ {
				stringTable[i] = append(stringTable[i], (*currentColum)[j])
				maxLen[i] = max(maxLen[i], len((*currentColum)[j]))
			}
		}
	}

	for i := 0; i < len(stringTable); i++ {
		currentword := stringTable[i][0]
		print(currentword)
		for j := len(currentword); j < maxLen[i]; j++ {
			print(" ")
		}
		if i < len(stringTable)-1 {
			print("│")
		}
	}
	println()
	for i := 0; i < len(maxLen); i++ {
		for j := 0; j < maxLen[i]; j++ {
			print("─")
		}
		if i < len(maxLen)-1 {
			print("┼")
		}
	}
	println()
	for i := 1; i < len(stringTable[0]); i++ {
		for j := 0; j < len(stringTable); j++ {
			currentWord := stringTable[j][i]
			print(currentWord)
			for k := len(currentWord); k < maxLen[j]; k++ {
				print(" ")
			}
			if j < len(stringTable)-1 {
				print("│")
			}
		}
		println()
	}

	/*for i := 0; i < len(r.Columns); i++ {//Datentyp
		println(r.Columns[i].Signature.Type)
	}*/
	println()

}

func (r *Relation) GetRawData() interface{} {
	return r.Columns
}

func (cs *ColumnStore) CreateRelation(tabName string, sig []AttrInfo) Relationer {
	// initialize a new map when no one exists
	if cs.Relations == nil {
		cs.Relations = make(map[string]Relationer)
	}

	// create an appropriate number of columns and asign the signatures
	var cols = make([]Column, len(sig))
	for i, s := range sig {
		cols[i].Signature = s
	}

	// create a new relation and asign the columns
	var rs = new(Relation)
	rs.Name = tabName
	rs.Columns = cols

	// save and return the relation
	cs.Relations[tabName] = rs
	return rs
}

func (cs *ColumnStore) NestedLoopJoin(leftRelation string, leftCol AttrInfo, rightRelation string, rightCol AttrInfo, comp Comparison) Relationer {
	//TODO 1
	var rs = new(Relation)
	rs.Name = "Result"

	rOrg := cs.Relations[rightRelation].GetRawData().([]Column)
	lOrg := cs.Relations[leftRelation].GetRawData().([]Column)
	rR := cs.Relations[rightRelation]
	lR := cs.Relations[leftRelation]

	lCpy := Relation{
		Name:    "",
		Columns: nil,
	}
	for _, col := range lR.GetRawData().([]Column) {
		lCpy.Columns = append(lCpy.Columns, Column{
			Signature: col.Signature,
			Data:      &([]string{}),
		})
	}

	rCpy := Relation{
		Name:    "",
		Columns: nil,
	}
	for _, col := range rR.GetRawData().([]Column) {
		rCpy.Columns = append(rCpy.Columns, Column{
			Signature: col.Signature,
			Data:      &([]string{}),
		})
	}

	rR = rR.Scan([]AttrInfo{rightCol})
	lR = lR.Scan([]AttrInfo{leftCol})

	lT := lR.GetRawData().([]Column)[0].Signature.Type
	rT := rR.GetRawData().([]Column)[0].Signature.Type

	if lT == rT {
		dt := lT
		lC := lR.GetRawData().([]Column)[0].Data.(*[]string)
		rC := rR.GetRawData().([]Column)[0].Data.(*[]string)
		for indexL, contentL := range *lC {
			for indexR, contentR := range *rC {
				if compare(dt, comp, contentL, contentR) {
					for index := range lCpy.Columns {
						*lCpy.Columns[index].Data.(*[]string) = append(*lCpy.Columns[index].Data.(*[]string), (*lOrg[index].Data.(*[]string))[indexL])
					}
					for index := range rCpy.Columns {
						*rCpy.Columns[index].Data.(*[]string) = append(*rCpy.Columns[index].Data.(*[]string), (*rOrg[index].Data.(*[]string))[indexR])
					}
				}
			}
		}
	}
	for _, c := range lCpy.Columns {
		rs.Columns = append(rs.Columns, c)
	}
	for _, c := range rCpy.Columns {
		rs.Columns = append(rs.Columns, c)
	}

	return rs
}

func compare(dt DataTypes, cp Comparison, val1 string, val2 string) bool {
	switch dt {
	case INT:
		v1, _ := strconv.Atoi(val1)
		v2, _ := strconv.Atoi(val2)
		switch cp {
		case EQ:
			return v1 == v2
		case GT:
			return v1 > v2
		case LT:
			return v1 < v2
		case LE:
			return v1 <= v2
		case GE:
			return v1 >= v2
		case NEQ:
			return v1 != v2
		}
		return false
	case FLOAT:
		v1, _ := strconv.ParseFloat(val1, 64)
		v2, _ := strconv.ParseFloat(val2, 64)
		switch cp {
		case EQ:
			return v1 == v2
		case GT:
			return v1 > v2
		case LT:
			return v1 < v2
		case LE:
			return v1 <= v2
		case GE:
			return v1 >= v2
		case NEQ:
			return v1 != v2
		}
		return false
	case STRING:
		v1 := val1
		v2 := val2
		switch cp {
		case EQ:
			return v1 == v2
		case GT:
			return v1 > v2
		case LT:
			return v1 < v2
		case LE:
			return v1 <= v2
		case GE:
			return v1 >= v2
		case NEQ:
			return v1 != v2
		}
		return false
	}
	return false
}

func Hash(s string, size int) int {
	ret := 0
	for _, i := range s {
		ret += int(i)
	}
	return ret % size
}

func (cs *ColumnStore) HashJoin(leftRelation string, leftCol AttrInfo, rightRelation string, rightCol AttrInfo, comp Comparison) Relationer {
	//TODO 2
	var rs = new(Relation)
	const hashTableSize = 3
	rs.Name = "Result"
	lOrg := cs.Relations[leftRelation]
	rOrg := cs.Relations[rightRelation]

	lRet := Relation{
		Name:    "",
		Columns: nil,
	}
	for _, column := range lOrg.GetRawData().([]Column) {
		lRet.Columns = append(lRet.Columns, Column{
			Signature: column.Signature,
			Data:      &([]string{}),
		})
	}
	rRet := Relation{
		Name:    "",
		Columns: nil,
	}
	for _, column := range rOrg.GetRawData().([]Column) {
		rRet.Columns = append(rRet.Columns, Column{
			Signature: column.Signature,
			Data:      &([]string{}),
		})
	}

	leftIsLoop := true
	hashRelation := rOrg
	hashRelation = hashRelation.Scan([]AttrInfo{rightCol})
	hashOrg := rOrg
	hashRet := rRet
	loopRelation := lOrg
	loopRelation = loopRelation.Scan([]AttrInfo{leftCol})
	loopOrg := lOrg
	loopRet := lRet
	dt := loopRelation.GetRawData().([]Column)[0].Signature.Type
	if loopRelation.GetRawData().([]Column)[0].Signature.Type != dt {
		println("Mismatch DataTypes")
	}
	if lOrg.Size() < rOrg.Size() {
		leftIsLoop = false
		temp := hashRelation
		tempOrg := hashOrg
		tempRet := hashRet
		hashRelation = loopRelation
		hashOrg = loopOrg
		hashRet = loopRet
		loopRelation = temp
		loopOrg = tempOrg
		loopRet = tempRet
	}

	var hashTable [hashTableSize][]int

	for index, str := range *hashRelation.GetRawData().([]Column)[0].Data.(*[]string) {
		hashVal := Hash(str, hashTableSize)
		hashTable[hashVal] = append(hashTable[hashVal], index)
	}

	for index, str := range *loopRelation.GetRawData().([]Column)[0].Data.(*[]string) {
		hashVal := Hash(str, hashTableSize)
		if len(hashTable[hashVal]) != 0 {
			for _, i := range hashTable[hashVal] {
				hashedString := (*hashRelation.GetRawData().([]Column)[0].Data.(*[]string))[i]
				if compare(dt, comp, str, hashedString) {
					for colIndex, column := range loopOrg.GetRawData().([]Column) {
						*loopRet.Columns[colIndex].Data.(*[]string) = append(*loopRet.Columns[colIndex].Data.(*[]string), (*column.Data.(*[]string))[index])
					}
					for colIndex, column := range hashOrg.GetRawData().([]Column) {
						*hashRet.Columns[colIndex].Data.(*[]string) = append(*hashRet.Columns[colIndex].Data.(*[]string), (*column.Data.(*[]string))[i])
					}
				}
			}
		}
	}

	lCpy := loopRet
	rCpy := hashRet

	if !leftIsLoop {
		temp := lCpy
		lCpy = rCpy
		rCpy = temp
	}

	for _, column := range lCpy.Columns {
		rs.Columns = append(rs.Columns, column)
	}

	for _, column := range rCpy.Columns {
		rs.Columns = append(rs.Columns, column)
	}

	return rs
}

func (cs *ColumnStore) GetRelation(relationName string) (Relationer, error) {
	var rs = cs.Relations[relationName]
	if rs == nil {
		return nil, errors.New("no relation named " + relationName + " exists")
	}
	return rs, nil
}

func max(a int, b int) int {
	if a > b {
		return a
	}
	return b
}

func isInt(s string) bool {
	if s == "-" {
		return false
	}
	for i := 0; i < len(s); i++ {
		if i == 0 && s[i] == 45 {
			continue
		}
		if !(s[i] >= 48 && s[i] <= 57) {
			return false
		}
	}
	return true
}
func isFloat(s string) bool {
	if s == "-" {
		return false
	}
	floatingPointDiscovered := false
	for i := 0; i < len(s); i++ {
		if i == 0 && s[i] == 45 {
			continue
		}
		if s[i] == 46 {
			if floatingPointDiscovered {
				return false
			}
			floatingPointDiscovered = true
			continue
		}
		if !(s[i] >= 48 && s[i] <= 57) {
			return false
		}
	}
	return true
}

func typeCheck(datatype DataTypes, word string) DataTypes {
	//Returns the "most specialized" datatype possible of given string
	if datatype == INT {
		if isInt(word) {
			return INT
		}
		datatype = FLOAT
	}
	if datatype == FLOAT {
		if isFloat(word) {
			return FLOAT
		}
	}
	return STRING
}

func (r *Relation) Size() int {
	if len(r.Columns) == 0 {
		return 0
	}
	return len(*r.Columns[0].Data.(*[]string))
}
