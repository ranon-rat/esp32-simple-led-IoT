#include <Arduino.h>
#include "esp_https_server.h"
#include "static.hpp"
#include "pins.hpp"
//states


static esp_err_t onled(httpd_req_t *req)
{
    String uri=String(req->uri);
    
   
    static bool  yellowState = LOW;
    static bool  greenState = LOW;
    static bool  redState = LOW;
    if (uri== String("/led?green")){// /led?green
        
        greenState = !greenState;
        }
    else if (uri==String("/led?red"))
        redState = !redState;
    else if (uri ==String("/led?yellow"))
        yellowState = !yellowState;
    
    

    
    Serial.printf("%d,%d,%d\n", yellowState, greenState, redState);
    digitalWrite(GREEN, greenState);
    digitalWrite(YELLOW, yellowState);
    digitalWrite(RED, redState);
    return httpd_resp_send(req, "cum chalice", strlen("cum chalice"));
}
static esp_err_t html_resp(httpd_req_t *req)
{
    httpd_resp_set_type(req, "text/html");

    return httpd_resp_send(req, (const char *)homepage_html, homepage_html_len);
}
void initServer()
{
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    httpd_handle_t server = NULL;
    config.server_port = 80;
    httpd_uri_t static_page = {
        .uri = "/",
        .method = HTTP_GET, //HTTP_GET
        .handler = html_resp,
        .user_ctx = NULL};
    httpd_uri_t led_handler = {
        .uri = "/led",
        .method = HTTP_GET, //HTTP_GET
        .handler = onled,
        .user_ctx = NULL};
    if (httpd_start(&server, &config) == ESP_OK)
    {
        httpd_register_uri_handler(server, &static_page);
        httpd_register_uri_handler(server, &led_handler);
    }
}