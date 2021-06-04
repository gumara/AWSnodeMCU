/*
  Copyright 2019 Amazon.com, Inc. or its affiliates. All Rights Reserved.
  Permission is hereby granted, free of charge, to any person obtaining a copy of this
  software and associated documentation files (the "Software"), to deal in the Software
  without restriction, including without limitation the rights to use, copy, modify,
  merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
  permit persons to whom the Software is furnished to do so.
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
  PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <pgmspace.h>

#define SECRET
#define THINGNAME "ESP32"

const char WIFI_SSID[] = "Toom_2.4G";
const char WIFI_PASSWORD[] = "25062493";
const char AWS_IOT_ENDPOINT[] = "agbkd4tjn5i4l-ats.iot.us-west-2.amazonaws.com";

// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";

// Device Certificate
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWjCCAkKgAwIBAgIVAK38zHwrmR6x0ybgwU1qYwPc/B/nMA0GCSqGSIb3DQEB
CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t
IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yMTA2MDMxNTI4
NDZaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh
dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDbCM8R9vAYQrky0lsz
rkoPDR4hOQW/Xonpi2jujwxdiAXIuZRAHI9JlaBY1rxrWsDEbOacmE32YkPbjfdt
dJJXqnKWNb+5DUz9g7c8Y1SzIYYnhG40iIPQ1DOccnG/Omh0/37wnGQA0HYJ6Im4
u+meFRneyr4Ph0Wyw/U0+pWZjwT3WKvcTSj7Dh+okBg3mdjD7Xu/XWnY9gHoswIw
LwEpiVjFsudkxINaWNeud8Hu+9+y9iN6gHpsz9PmePckE4+ZAcCEYDlWXYLIc+RE
TDJvIZOzWF2IL4IswXd6eSevcDxlnq/YWAtIIQ0p081Ec1dwo7WPIdbQeOdTB3Aj
UyDvAgMBAAGjYDBeMB8GA1UdIwQYMBaAFBYmvEZav+LucM0tv1VTdpHI/CNzMB0G
A1UdDgQWBBT0OTqC+c0d/asm5ed1dSV1c47C2DAMBgNVHRMBAf8EAjAAMA4GA1Ud
DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAkSqcRoaOpiFNIS96khzuShQ2
/uoTHETc3RIt2/SpwsnNa7clRCL+ZFvejVtfqzvCck2VuthMnj04n08Cx94w8DFu
gO8eJqg598mpkbriRRthYASI8Stof2QIsNCAu5wfo5HlHDxj4NBeenWneal5s8Fh
IipcEPOmPqqIMiHO6anokkiBFDMe7dC25DNJmFVm9BdjQdWqS3hsDrS+6jvGwEPW
OiwK8EjzaakZEqHiCPmgpM5Pk46Tq68j3dEYTz8IsGELeYw1nVNYqyI4AIG4oGw5
Q3/ZMXSMLNJ6hSZ2P9TKlUZHmAdP76E8NoqBL3sM0uQCiv4vZtv6THk9eQNOfg==
-----END CERTIFICATE-----
)KEY";

// Device Private Key
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEpQIBAAKCAQEA2wjPEfbwGEK5MtJbM65KDw0eITkFv16J6Yto7o8MXYgFyLmU
QByPSZWgWNa8a1rAxGzmnJhN9mJD2433bXSSV6pyljW/uQ1M/YO3PGNUsyGGJ4Ru
NIiD0NQznHJxvzpodP9+8JxkANB2CeiJuLvpnhUZ3sq+D4dFssP1NPqVmY8E91ir
3E0o+w4fqJAYN5nYw+17v11p2PYB6LMCMC8BKYlYxbLnZMSDWljXrnfB7vvfsvYj
eoB6bM/T5nj3JBOPmQHAhGA5Vl2CyHPkREwybyGTs1hdiC+CLMF3enknr3A8ZZ6v
2FgLSCENKdPNRHNXcKO1jyHW0HjnUwdwI1Mg7wIDAQABAoIBAQC58Zx4j737molG
T7YFBazxYh117samU0eY8DTAcMf6jwL6CDGGy7gIq/FX+dQy/vQuzJRp1BI7W+hn
dvnZ/eBOc/Ca/D4qhtQZU7w2k8zP1WHiIla8WjgtDDhUVAOkZ51N1aiZ8uoiltXe
S36/SSdmgFtZ+5ul6xyMSjbcJu7hUCodzo7ucAglHUrY2mTShxhT6oU2hDkpuSQX
39PNqfhhN2npqyqzZeeU9SpPGL1zcn6EFrifnrURoOlntUj2oTkWInE39XFi8Q5s
pzqaHNJ8SGhpO+8Gwuw6/FcSdw4IA2Fwgk6OiWsgbn2p9Ph+vfSlalaGsiDQ+ZR2
rO5QiQwBAoGBAPq4W9HvjpFRiYlqK+bxPoyh5n38msS55nOln2E5mrurEu71h99E
bRvXdy5i2P3KCN3hL06Gm4hhIRJ4QeXduDhqvIYNj764lZ6bzEj3taBhZGRqzrC3
NBYJMu0QmUNM52T0cV/RzjsA1L8MQGw/URUkGijxvlxvccu2gGfF1qCBAoGBAN+l
oZgaSLspK7nd2YAefbPHKle9YR3VQ1vAyRtjgyUkIUrn1RhwqNpK0LtU2HubpUW0
c4alRQ4YBgURPMBrp4WHQzA4Pgox1zLB5WWWEKHNtj4hAGNr+6XeIRMY4Zn+qR4s
ovt3rRbH6D54C1VxxPJZWiMqcbUmw4kC+89gHwlvAoGAKPf5IQvpGvvc4pRzyg//
rZFDDbE6RQ0viBQ3P/bevu3McTmz0xrmTVdfBThnxsi9vCvww/8g6R8d/VujQQGC
+c0PM0SCCaM1564DqqS3jBZ+Bh6h2aSGIVetd6lvsdyeLxP2drbc4S1YlkNVP5r1
D+RPVgNynL4lNSmEP/DHCoECgYEAtSFaLOwst5hyl4g73W3UdMP7YTA59YWBllAf
EJWZ43zNkfMNPUwRFSq+vtnKsuGuCzRI1GYJ9Y4zYetB/r2x4Y1ZNzZ12J/hIHS1
K39MXR9UWCE2RU9xcjbjJqpiHOyJX6zbGzsj7m1dhSqIU11fGsCPJif8C7EncFIA
S0YYHPUCgYEA10X6xN9BFO+V2vVKp0gwY4Mp2VWLKhCCbK05NJ8qjDjjjnV6TUH0
cjjmv7XMaYbMHGUOdq4gdTjjTKxI53M/KPpVVQT0JutpYofWrbAHnWCZvCptFSeV
x3dwRHOSfC3ZNrEydIyTPUf5n3P2Q7dkQj70Mt8lHsp6Z8hYhQp6Y0Q=
-----END RSA PRIVATE KEY-----
)KEY";
