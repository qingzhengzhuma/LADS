// Polynomial.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

using namespace std;

struct PolynomialItem
{
	float Coeff;
	int Power;
	PolynomialItem* next;
};

struct Polynomial
{
	int ItemCount;
	PolynomialItem *FirstItem;
	PolynomialItem *LastItem;
};

PolynomialItem* CreatePolyItem(float Coeff,int Power)
{
	if(Coeff == 0.0f) return NULL;
	PolynomialItem* PolyItem = new PolynomialItem;
	PolyItem->Coeff = Coeff;
	PolyItem->Power = Power;
	PolyItem->next = NULL;
	return PolyItem;
}

PolynomialItem* CopyPolyItem(const PolynomialItem* Item)
{
	if(Item == NULL) return NULL;
	return CreatePolyItem(Item->Coeff,Item->Power);
}

Polynomial* CreateEmptyPolynomial()
{
	Polynomial* Poly = new Polynomial;
	Poly->ItemCount = 0;
	Poly->FirstItem = NULL;
	Poly->LastItem = NULL;
	return Poly;
}

void AppendPolyItem(Polynomial** Poly,PolynomialItem *Item)
{
	if((*Poly)->ItemCount == 0) 
	{
		(*Poly)->FirstItem = Item;
		(*Poly)->LastItem = Item;
		++(*Poly)->ItemCount;
		return;
	}
	Item->next = NULL;
	(*Poly)->LastItem->next = Item;
	(*Poly)->LastItem = Item;
	++(*Poly)->ItemCount;
}

void AppendPolyItem(Polynomial** Poly,float Coeff,int Power)
{
	AppendPolyItem(Poly,CreatePolyItem(Coeff,Power));
}

void InsertPolyItem(Polynomial** Poly,PolynomialItem *Item)
{
	if((*Poly)->ItemCount == 0)
	{
		AppendPolyItem(Poly,Item);
		return;
	}
	if((*Poly)->FirstItem->Power < Item->Power)
	{
		Item->next = (*Poly)->FirstItem;
		(*Poly)->FirstItem = Item;
		++(*Poly)->ItemCount;
		return;
	}
	PolynomialItem* p = (*Poly)->FirstItem;
	PolynomialItem* q;
	while(p)
	{
		if(p->Power > Item->Power)
		{
			q = p;
			p = p->next;
		}
		else if(p->Power == Item->Power) 
		{
			p->Coeff += Item->Coeff;
			return;
		}
		else
		{
			Item->next = q->next;
			q->next = Item;
			++(*Poly)->ItemCount;
			return;
		}
	}
	AppendPolyItem(Poly,Item);
	return;
}

void InsertPolyItem(Polynomial** Poly,float Coeff,int Power)
{
	InsertPolyItem(Poly,CreatePolyItem(Coeff,Power));
}

Polynomial* CreatePolynomial(float Coeffs[],int Powers[],int Count)
{
	if(Count <= 0) return NULL;
	Polynomial* Poly = CreateEmptyPolynomial();
	for (int i = 0; i < Count; ++i)
	{
		InsertPolyItem(&Poly,Coeffs[i],Powers[i]);
	}
	return Poly;
}

PolynomialItem* ItemPlus(const PolynomialItem* item1,const PolynomialItem* item2)
{
	if(item1->Power != item2->Power) return NULL;
	float Coeff = item1->Coeff + item2->Coeff;
	int Power = item1->Power;
	return CreatePolyItem(Coeff,Power);
}

PolynomialItem* ItemMinus(const PolynomialItem* item1,const PolynomialItem* item2)
{
	if(item1->Power != item2->Power) return NULL;
	float Coeff = item1->Coeff - item2->Coeff;
	int Power = item1->Power;
	return CreatePolyItem(Coeff,Power);
}

PolynomialItem* ItemMulti(const PolynomialItem* item1,const PolynomialItem* item2)
{
	float Coeff = item1->Coeff * item2->Coeff;
	int Power = item1->Power + item2->Power;
	return CreatePolyItem(Coeff,Power);
}

Polynomial* Plus(const Polynomial* Poly1,const Polynomial* Poly2)
{
	Polynomial* Poly = CreateEmptyPolynomial();
	PolynomialItem* p = Poly1->FirstItem,*q = Poly2->FirstItem;
	while(p && q)
	{
		PolynomialItem* newItem = NULL;
		if(p->Power == q->Power)
		{
			newItem = ItemPlus(p,q);
			p = p->next;
			q = q->next;
		}
		else if(p->Power > q->Power)
		{
			newItem = CopyPolyItem(p);
			p = p->next;
		}
		else
		{
			newItem = CopyPolyItem(q);
			q = q->next;
		}
		AppendPolyItem(&Poly,newItem);
	}
	while(p)
	{
		AppendPolyItem(&Poly,CopyPolyItem(p));
		p = p->next;
	}
	while(q)
	{
		AppendPolyItem(&Poly,CopyPolyItem(q));
		q = q->next;
	}
	return Poly;
}
Polynomial* Minus(const Polynomial* Poly1,const Polynomial* Poly2)
{
	Polynomial* Poly = CreateEmptyPolynomial();
	PolynomialItem* p = Poly1->FirstItem,*q = Poly2->FirstItem;
	while(p && q)
	{
		PolynomialItem* newItem = NULL;
		if(p->Power == q->Power)
		{
			newItem = ItemMinus(p,q);
			p = p->next;
			q = q->next;
		}
		else if(p->Power > q->Power)
		{
			newItem = CopyPolyItem(p);
			p = p->next;
		}
		else
		{
			newItem = CopyPolyItem(q);
			newItem->Coeff = -newItem->Coeff;
			q = q->next;
		}
		AppendPolyItem(&Poly,newItem);
	}
	while(p)
	{
		AppendPolyItem(&Poly,CopyPolyItem(p));
		p = p->next;
	}
	while(q)
	{
		PolynomialItem* newItem = CopyPolyItem(q);
		newItem->Coeff = -newItem->Coeff;
		AppendPolyItem(&Poly,newItem);
		q = q->next;
	}
	return Poly;
}
Polynomial* Multi(const Polynomial* Poly1,const Polynomial* Poly2)
{
	Polynomial* Poly = CreateEmptyPolynomial();
	PolynomialItem* q = Poly2->FirstItem;
	PolynomialItem* p = Poly1->FirstItem;
	while(q)
	{
		AppendPolyItem(&Poly,ItemMulti(p,q));
		q = q->next;
	}
	p = p->next;
	Polynomial* tempPoly = CreateEmptyPolynomial();
	while(p)
	{
		q = Poly2->FirstItem;
		while(q)
		{
			AppendPolyItem(&tempPoly,ItemMulti(p,q));
			q = q->next;
		}
		PolynomialItem* r = tempPoly->FirstItem;
		PolynomialItem* s = Poly->FirstItem,*t = NULL;
		while(s && s->Power >= r->Power) 
		{
			t = s;
			s = s->next;
		}
		while(r && s)
		{
			tempPoly->FirstItem = r->next;
			if(t->Power > r->Power)
			{
				r->next = t->next;
				t->next = r;
				t = r;
				++Poly->ItemCount;
			}
			else if(t->Power == r->Power)
			{
				t->Coeff += r->Coeff;
				delete r;
			}
			r = tempPoly->FirstItem;
			--tempPoly->ItemCount;
			while(r && s && s->Power >= r->Power)
			{
				t = s;
			    s = s->next;
		    }
		}
		if(r)
		{
			if(r->Power == Poly->LastItem->Power)
			{
				Poly->LastItem->Coeff += r->Coeff;
				tempPoly->FirstItem = r->next;
				--tempPoly->ItemCount;
				delete r;
			}
			Poly->LastItem->next = tempPoly->FirstItem;
			Poly->LastItem = tempPoly->LastItem;
			Poly->ItemCount += tempPoly->ItemCount;	
		}
		tempPoly->FirstItem = NULL;
		tempPoly->LastItem = NULL;
		tempPoly->ItemCount = 0;
		p = p->next;
	}
	return Poly;
}
void Display(const Polynomial* Poly)
{
	if(Poly->ItemCount == 0) return;
	cout<<Poly->FirstItem->Coeff<<"X^"<<Poly->FirstItem->Power;
	PolynomialItem* p = Poly->FirstItem->next;
	while(p)
	{
		if(p->Coeff > 0)
		{
			cout<<'+'<<p->Coeff<<"x^"<<p->Power;
		}
		else if(p->Coeff < 0)
		{
			cout<<p->Coeff<<"x^"<<p->Power;
		}
		p = p->next;
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	float Coeffs[] = {2, 1,-98,76,52};
	int Powers[] = {1,4,6,-4,1};

	float Coeffs1[] = {4, 2};
	int Powers1[] = {4,1};
	Polynomial * poly1 = CreatePolynomial(Coeffs,Powers,5);
	Polynomial * poly2 = CreatePolynomial(Coeffs1,Powers1,2);
	Polynomial * poly = Multi(poly1,poly2);
	Display(poly);
	cout<<endl;
	return 0;
}

