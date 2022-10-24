import java.io.IOException;
import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.io.File;  // Import the File class
import java.io.FileWriter;   // Import the FileWriter class


class dpm {

    public static void main(String[] args) throws IOException, InterruptedException {

        File check = new File("modules_doS");
        if (!check.exists())
        {
          check.mkdirs();
        }
        HttpClient client = HttpClient.newHttpClient();
        // i'll update url
        HttpRequest request = HttpRequest.newBuilder()
                .uri(URI.create("http://localhost:3000/pack/"+args[0]))
                .build();

        HttpResponse<String> response = client.send(request,
                HttpResponse.BodyHandlers.ofString());
        String[] test = response.body().split(",");
        System.out.println("get data => downloading");
        FileWriter myWriter = new FileWriter("modules_doS/"+test[0]+".do");
        System.out.println("Successfully download!");
        myWriter.write(test[1]);

        myWriter.close();
    }
}
