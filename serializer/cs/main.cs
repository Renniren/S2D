using System;
using System.Threading;
using System.Threading.Tasks;

class SerializerEntry
{
    static async Task Main(string[] args)
    {
        int delay = 10000;
        int i = 0;
        while (true)
        {
            i++;
            if (i >= delay) break;
            await Task.Delay(1200);
        }

        Console.WriteLine("d");
    }
}
