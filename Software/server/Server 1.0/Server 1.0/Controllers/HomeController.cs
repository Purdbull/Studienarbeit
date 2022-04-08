using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Logging;
using Server_1._0.Models;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;

namespace Server_1._0.Controllers
{
    public class HomeController : Controller
    {
        private readonly ILogger<HomeController> _logger;

        private Services.IMqttService _mqttService;

        public HomeController(ILogger<HomeController> logger, Services.IMqttService mqttService)
        {
            _logger = logger;
            _mqttService = mqttService;
        }

        public IActionResult Index()
        {
            return View();
        }

        public IActionResult Info()
        {
            return View();
        }

        [ResponseCache(Duration = 0, Location = ResponseCacheLocation.None, NoStore = true)]
        public IActionResult Error()
        {
            return View(new ErrorViewModel { RequestId = Activity.Current?.Id ?? HttpContext.TraceIdentifier });
        }

        [HttpPost]
        [Route("Home/Position")]
        public IActionResult driveTo(int position)
        {
            string topic = "Train/driveToPosition";
            string message = position.ToString();
            _mqttService.sendMessage(topic, message);
            return Ok();
        }

        [HttpGet]
        [Route("Home/Warn")]
        public IActionResult getWarningMsg()
        {
            return Content(_mqttService.getWarningMsg());
        }

        [HttpGet]
        [Route("Home/Battery")]
        public IActionResult getBatteryVal()
        {
            return Content(_mqttService.getBatteryVal());
        }

        [HttpGet]
        [Route("Home/Error")]
        public IActionResult getErrorMsg()
        {
            return Content(_mqttService.getErrorMsg());
        }

        [HttpGet]
        [Route("Home/Position")]
        public IActionResult getPosition()
        {
            return Content(_mqttService.getPosition());
        }
    }
}
