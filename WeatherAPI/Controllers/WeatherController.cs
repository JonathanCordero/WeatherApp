using Microsoft.AspNetCore.Mvc;

[ApiController]
[Route("api/[controller]")]
public class WeatherController : ControllerBase
{
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