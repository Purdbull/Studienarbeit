using MQTTnet.Server;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

using System;
using System.Collections.Generic;
using System.Globalization;
using System.Reflection;
using System.Runtime.Versioning;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Extensions.Logging;
using MQTTnet;
using MQTTnet.AspNetCore;
using MQTTnet.Client.Receiving;
using MQTTnet.Server;
using Microsoft.AspNetCore.Mvc;

namespace Server_1._0.Services
{
    public class MqttService : Controller, IMqttService
    {
        private readonly IMqttServer _mqttServer;
        private string ErrorMsg = "Nix schlimm kaputt :)";
        private string WarnMsg = "Nix kaputt ^^";
        private string BatteryVal = "Keine Info :(";
        private string Position = "0";
        public MqttService(IMqttServer mqttServer)
        {
            _mqttServer = mqttServer;
            Console.WriteLine("hi");
            _mqttServer.UseApplicationMessageReceivedHandler(async e =>
            {
                try
                {
                    string topic = e.ApplicationMessage.Topic;
                    string[] words = topic.Split("/");
                    string id = e.ClientId;
                    if (string.IsNullOrWhiteSpace(topic) == false)
                    {
                        string payload = Encoding.UTF8.GetString(e.ApplicationMessage.Payload);
                        Console.WriteLine($"Topic: {topic}. Message Received: {payload}. Client: {id}");
                        if(topic == "Train/Error")
                        {
                            this.ErrorMsg = payload;
                        }
                        else if(topic == "Train/Warning")
                        {
                            this.WarnMsg = payload;
                        }
                        else if(topic == "Train/Battery")
                        {
                            this.BatteryVal = payload + "%";
                        }
                        else if(topic == "Train/Position")
                        {
                            this.Position = payload;
                        }
                    }
                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex.Message, ex);
                }
            });
        }

        public string getErrorMsg()
        {
            return this.ErrorMsg;
        }

        public string getWarningMsg()
        {
            return this.WarnMsg;
        }

        public string getBatteryVal()
        {
            return this.BatteryVal;
        }

        public string getPosition()
        {
            return this.Position;
        }

        public void receiveMessage()
        {
            _mqttServer.UseApplicationMessageReceivedHandler(async e =>
            {
                try
                {
                    string topic = e.ApplicationMessage.Topic;
                    if (string.IsNullOrWhiteSpace(topic) == false)
                    {
                        string payload = Encoding.UTF8.GetString(e.ApplicationMessage.Payload);
                        Console.WriteLine($"Topic: {topic}. Message Received: {payload}");
                    }
                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex.Message, ex);
                }
            });
        }

        public Task sendMessage(string topic, string payload)
        {
            var msg = new MqttApplicationMessageBuilder()
                        .WithPayload(payload)
                        .WithTopic(topic);

            this._mqttServer.PublishAsync(msg.Build());
            return Task.CompletedTask;
        }
    }
}
