#include <stdio.h>
#include <curl/curl.h>

int main(void) {
  CURL *curl;
  CURLcode output;

  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();
  if (curl)
  {
    curl_easy_setopt(curl,CURLOPT,"http://localhost:3000/pack/all");
    output = curl_easy_perform(curl);

    if (output != CURLE_OK)
    {
      printf("failed res");
    } else {
      printf("%s",output)
    }
  }
}



