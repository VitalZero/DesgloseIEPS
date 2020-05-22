#pragma once

class Combust
{
public:
	Combust(double litros, double importe, double flete, double iva, double retencion)
	{
		impActual = importe;
		this->litros = litros;
		this->flete = flete;
		this->iva = iva;
		ret = retencion;
		subTotal = 0;
		total = 0;
		ieps = 0;
		impReal = 0;

		Desglosa();
	}
	double PrecioRealUnit() const { return impReal / 1000; }
	double Ieps() const { return ieps; }
	double Total() const { return total; }

private:
	void Desglosa()
	{
		subTotal = impActual + flete;
		impReal = (iva - (flete * 0.16)) / 0.16;
		ieps = subTotal - impReal - flete;
		total = impReal + ieps + flete + iva - ret;
	}

private:
	double impActual;
	double litros;
	double flete;
	double iva;
	double ret;
	double subTotal;
	double total;
	double ieps;
	double impReal;
};
