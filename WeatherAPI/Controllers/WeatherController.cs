using Microsoft.AspNetCore.Mvc;
using System.Net.Http;
using System.Threading.Tasks;

[ApiController]
[Route("api/[controller]")]
public class WeatherController : ControllerBase{

    private const string ApiKey = "N/A";//Not including my ApiKey in the github.
    private const string WeatherApiUrl = "http://api.weatherapi.com/v1/current.json";
    
    //https://api.weatherapi.com/v1/current.json?q=bronx&lang=English&key=??? example of the end request for reminder. Break.

    [HttpGet]
    public async Task<IActionResult> GetWeather([FromQuery] string city){
        
        if (string.IsNullOrWhiteSpace(city)){
            return BadRequest(new { error = "City parameter is required." });
        }

        try{
            using var httpClient = new HttpClient();
            var requestUrl = $"{WeatherApiUrl}?key={ApiKey}&q={city}";
            var response = await httpClient.GetAsync(requestUrl);

            if (!response.IsSuccessStatusCode){
                return StatusCode((int)response.StatusCode, new { error = "Failed to fetch weather data." });
            }

            var weatherData = await response.Content.ReadAsStringAsync();
            return Ok(weatherData);
        }
        catch (HttpRequestException ex){
            return StatusCode(500, new { error = "Error communicating with WeatherAPI.", details = ex.Message });
        }
    }
}