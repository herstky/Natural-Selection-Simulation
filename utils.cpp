#include "utils.h"

void sigmoid(arma::mat pMatrix)
{
	for (int m = 0; m < pMatrix.n_rows; m++)
	{
		for (int n = 0; n < pMatrix.n_cols; n++)
		{
			pMatrix(m, n) = 1 / (1 + exp(-pMatrix(m, n)));
		}
	}
}