using Microsoft.AspNetCore.Mvc;
using System.Net.Http;
using System.Threading.Tasks;

[ApiController]
[Route("api/[controller]")]
public class WeatherController : ControllerBase{
    private readonly HttpClient _httpClient;
    private const string ApiKey = "N/A";//Not including my ApiKey in the github.
    private const string WeatherApiUrl = "http://api.weatherapi.com/v1/current.json";
    //https://api.weatherapi.com/v1/current.json?q=bronx&lang=English&key=??? example of the end request for reminder. Break.
    [HttpGet]
    public IActionResult GetWeather([FromQuery] string city)
    {
        if (string.IsNullOrWhiteSpace(city))
        {
            return BadRequest(new { error = "City parameter is required." });
        }

        // Mock response (replace this with actual API call or logic)
        var weatherData = new
        {
            City = city,
            Temperature = "15°C",
            Condition = "Cloudy"
        };

        return Ok(weatherData);
    }
}