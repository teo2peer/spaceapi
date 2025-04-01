<?php

// Define the path to the spaceapi.json file
$spaceApiFile = 'spaceapi.json';

// Check if the POST body contains the 'open' key
if (isset($_POST['open'])) {
    // Get the 'open' value from the POST body
    $isOpen = filter_var($_POST['open'], FILTER_VALIDATE_BOOLEAN);

    // Read the current content of the spaceapi.json file
    $spaceApiData = file_get_contents($spaceApiFile);

    // Check if the file exists and the content was read successfully
    if ($spaceApiData !== false) {
        // Decode the JSON data into an associative array
        $spaceApiArray = json_decode($spaceApiData, true);

        // Check if decoding was successful
        if ($spaceApiArray !== null) {
            // Update the 'open' value
            $spaceApiArray['state']['open'] = $isOpen;

            // Encode the array back to JSON format
            $newSpaceApiData = json_encode($spaceApiArray, JSON_PRETTY_PRINT);

            // Save the updated data back to the spaceapi.json file
            if (file_put_contents($spaceApiFile, $newSpaceApiData) !== false) {
                echo 'The "open" status has been updated successfully.';
            } else {
                echo 'Error saving the updated spaceapi.json file.';
            }
        } else {
            echo 'Error decoding spaceapi.json.';
        }
    } else {
        echo 'Error reading spaceapi.json.';
    }
} else {
    echo 'No "open" value provided in the POST body.';

}




