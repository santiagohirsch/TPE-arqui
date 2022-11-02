using System;
using System.Text;
using SixLabors.ImageSharp;
using SixLabors.ImageSharp.PixelFormats;

namespace VesaFontMaker
{
    class Program
    {
        static void Main(string[] args)
        {
            using Image<Rgba32> image = Image.Load<Rgba32>("font.png");

            const int charWidth = 9;
            const int charHeight = 16;
            const int firstChar = 33;
            const int lastChar = 126;

            StringBuilder builder = new();
            builder.Append("char font[] = {\n");
            for (int i = 0; i <= (lastChar - firstChar); i++)
            {
                builder.Append("    ");

                int x = charWidth * i;
                for (int y = 0; y < charHeight; y++)
                {
                    byte b1 = 0;
                    for (int j = 0; j < 8; j++)
                        b1 = (byte)(b1 | ((image[x+j, y].R >= 10 ? 1 : 0) << j));
                    byte b2 = image[x+8, y].R >= 127 ? (byte)1 : (byte)0;

                    builder.Append("0x");
                    builder.Append(b1.ToString("X2"));
                    builder.Append(", 0x");
                    builder.Append(b2.ToString("X2"));
                    builder.Append((i != (lastChar-firstChar) || y != charHeight-1) ? ", " : "  ");
                }

                builder.AppendFormat("/* '{0}' */\n", (char)(firstChar + i));
            }
            builder.Append("};");

            string text = builder.ToString();
            Console.WriteLine(text);
            System.IO.File.WriteAllText("output.c", text, Encoding.UTF8);
        }
    }
}
