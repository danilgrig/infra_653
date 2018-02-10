/*
Сделать класс TComplex, у которого есть операторы +, -, *, ~, ...

*/

int main() {
	TComplex a(1, -1), b(2, 2), c;
	c = a + b;
	c = a - b;
	c.print();
	cin << c.abs() << endl;
}
