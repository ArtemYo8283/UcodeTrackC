double mx_pow(double n, unsigned int pow)
{
    double buf = n;
    if (pow == 0)
    {
        return 1;
    }
    for (unsigned int i = 1; i < pow; i++)
    {
        n *= buf;
    }
    return n;
}

