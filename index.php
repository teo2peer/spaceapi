<?php

header('Content-Type: application/json');
$filePath = 'spaceapi.json';

if (!file_exists($filePath)) {
    http_response_code(404);
    echo json_encode(["error" => "File not found"]);
    exit;
}

$jsonData = file_get_contents($filePath);

echo $jsonData;

?>
