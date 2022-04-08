using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace Server_1._0.Services
{
    public interface IMqttService
    {
        Task sendMessage(string topic, string payload);
        void receiveMessage();
    }
}
