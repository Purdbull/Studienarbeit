using MQTTnet.AspNetCore.Extensions;

using Microsoft.AspNetCore.Hosting;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;





namespace Server_1._0
{
    public class Program
    {
        public static void Main(string[] args)
        {
            CreateHostBuilder(args).Build().Run();
        }

        public static IHostBuilder CreateHostBuilder(string[] args) =>
            Host.CreateDefaultBuilder(args)
                .ConfigureWebHostDefaults(webBuilder =>
                {
                   
                    webBuilder.UseKestrel(
                    o =>
                    {
                        o.ListenAnyIP(1883, l => l.UseMqtt()); // MQTT pipeline
                        o.ListenAnyIP(5000); // Default HTTP pipeline
                    });
                   

                    webBuilder.UseStartup<Startup>();
                });


    }
}
