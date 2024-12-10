//need to tackle warning. I've abandoned the idea of using Lambda due to lambda costs. Next time ill use an api that doesn't have a key.
using Microsoft.OpenApi.Models;
var builder = WebApplication.CreateBuilder(args);

// Add services to the container.
builder.Services.AddControllers();
builder.Services.AddSwaggerGen(c => {
    c.SwaggerDoc("v1", new OpenApiInfo
    {
        Title = "Weather API",
        Version = "v1",
        Description = "Documentation for Weather App API."
    });
}); // Provides Swagger documentation

// CORS configuration
builder.Services.AddCors(options => {
    options.AddPolicy("AllowAll", builder => {
        builder.AllowAnyOrigin()  // Allow all origins
               .AllowAnyMethod()  // Allow all HTTP methods
               .AllowAnyHeader(); // Allow all headers
    });
});

var app = builder.Build();

// Use CORS
app.UseCors();

// Authorization
app.UseAuthorization();

// HTTPS redirection in local development
if (app.Environment.IsDevelopment())
{
    app.UseHttpsRedirection();
    app.UseDeveloperExceptionPage(); // Detailed errors in development
    app.UseSwagger();
    app.UseSwaggerUI(c => {
        c.SwaggerEndpoint("/swagger/v1/swagger.json", "Weather API v1");
    });
}

// Use HTTPS
app.UseHttpsRedirection();

// Map controllers
app.MapControllers();

app.Run();