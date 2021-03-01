#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

static char	*ft_base(long nbr, char *base)
{
	char	*str;
	long	nbr_copy;
	int		len_nbr;
	int		len_base;

	if (nbr < 0)
		nbr *= -1;
	nbr_copy = nbr;
	len_base = 0;
	while (base[len_base])
		len_base++;
	len_nbr = 0;
	while (nbr_copy >= len_base)
	{
		nbr_copy /= len_base;
		len_nbr++;
	}
	len_nbr++;
	str = (char *)malloc(len_nbr + 1);
	if (!str)
		return (NULL);
	str[len_nbr--] = '\0';
	while (nbr >= len_base)
	{
		str[len_nbr--] = base[nbr % len_base];
		nbr /= len_base;
	}
	str[len_nbr] = base[nbr];
	return (str);
}

int			ft_printf(const char *format, ...)
{
	va_list	args;
	char	*fmt;
	char	*str;
	long	nbr;
	int		width;
	int		dot;
	int		precision;
	int		printed;
	int		len;
	int		i;
	int		j;

	fmt = (char *)format;
	printed = 0;
	i = 0;
	va_start(args, format);
	while (fmt[i] != '\0')
	{
		if (fmt[i] == '%')
		{
			str = NULL;
			nbr = 0;
			width = 0;
			dot = 0;
			precision = 0;
			len = 0;
			j = 0;
			i++;
			while (fmt[i] >= '0' && fmt[i] <= '9')
				width = (width * 10) + fmt[i++] - 48;
			if (fmt[i] == '.')
			{
				dot = 1;
				i++;
				while (fmt[i] >= '0' && fmt[i] <= '9')
					precision = (precision * 10) + fmt[i++] - 48;
			}
			if (fmt[i] == 's')
			{
				str = va_arg(args, char *);
				if (!str)
					str = "(null)";
			}
			else if (fmt[i] == 'd')
			{
				nbr = (long)va_arg(args, int);
				str = ft_base(nbr, "0123456789");
			}
			else if (fmt[i] == 'x')
			{
				nbr = (long)va_arg(args, unsigned);
				str = ft_base(nbr, "0123456789abcdef");
			}
			while (str[len])
				len++;
			if (fmt[i] == 's')
			{
				if (len < precision || !dot)
					precision = len;
				width = width - precision;
				while (width-- > 0)
					printed += write(1, " ", 1);
				while (j < precision)
					printed += write(1, &str[j++], 1);
			}
			else if (fmt[i] == 'd' || fmt[i] == 'x')
			{
				if (nbr == 0 && dot && precision == 0)
				{
					while (width-- > 0)
						printed += write(1, " ", 1);
				}
				else
				{
					if (nbr < 0)
						width--;
					if (len <= precision)
						width -= precision;
					else
						width -= len;
					while (width-- > 0)
						printed += write(1, " ", 1);
					if (nbr < 0)
						printed += write(1, "-", 1);
					precision -= len;
					while (precision-- > 0)
						printed += write(1, "0", 1);
					while (j < len)
						printed += write(1, &str[j++], 1);
				}
				if (str)
					free(str);
			}
		}
		else
			printed += write(1, &fmt[i], 1);
		i++;
	}
	va_end(args);
	return (printed);
}