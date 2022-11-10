#pragma once

template <class T>
bool getBit(T var, unsigned int n_bit)
{
	return (bool((1 << n_bit) & var));
}

template <class T>
void setBit(T& var, unsigned int n_bit, bool bit)
{
	if (bit) var |= (1 << n_bit);
	else var &= ~(1 << n_bit);
}
