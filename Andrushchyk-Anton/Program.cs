using System.Text;

class Program
{
    static double Calculator_Pow(double a, double b) => Math.Pow(a, b);
    static bool Calculator_Eq(double a, double b) => a == b;
    static double Calculator_Log(double a, double b) => Math.Log(a, b);
    static int Calculator_And(int a, int b) => a & b;

    static void Main()
    {
        Console.OutputEncoding = Encoding.UTF8;
        Console.InputEncoding = Encoding.UTF8;

        Console.WriteLine("Доступні команди: **, ==, log, &");
        Console.WriteLine("Вводити дані у форматі: [число] [операція] [число]");
        Console.WriteLine("Для виходу введіть 'exit'");

        while (true)
        {
            Console.Write("\nВвід: ");
            string input = Console.ReadLine();

            if (string.IsNullOrWhiteSpace(input) || input.ToLower() == "exit") break;

            string[] parts = input.Split(' ', StringSplitOptions.RemoveEmptyEntries);

            if (parts.Length != 3)
            {
                Console.WriteLine("Помилка! Формат: [число] [операція] [число]");
                continue;
            }

            try
            {
                double a = double.Parse(parts[0]);
                string op = parts[1];
                double b = double.Parse(parts[2]);

                switch (op)
                {
                    case "**":
                        Console.WriteLine($"Результат: {Calculator_Pow(a, b)}");
                        break;
                    case "==":
                        Console.WriteLine($"Результат: {Calculator_Eq(a, b)}");
                        break;
                    case "log":
                        if (a <= 0 || b <= 0 || b == 1)
                            Console.WriteLine("Помилка: Неприпустимі аргументи.");
                        else
                            Console.WriteLine($"Результат: {Calculator_Log(a, b)}");
                        break;
                    case "&":
                        Console.WriteLine($"Результат: {Calculator_And((int)a, (int)b)}");
                        break;
                    default:
                        Console.WriteLine($"Невідома операція: {op}");
                        break;
                }
            }
            catch (FormatException)
            {
                Console.WriteLine("Помилка: Вводьте тільки числа.");
            }
        }
    }
}