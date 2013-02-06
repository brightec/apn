<?php

class AppNotification
{

  private $deviceToken;
  private $message;

  function __construct($deviceToken, $message)
  {
    $this->deviceToken = $deviceToken;
    $this->message = $message;
  }

  public function getAPNPayload()
  {
    $payload = new stdClass;
    $payload->aps = new stdClass;
    $payload->aps->alert = $this->message;
    $payload->aps->sound = 'default';

    // encode the payload
    $jsonPayload = json_encode($payload);

    return $jsonPayload;
  }

  public function getDeviceToken()
  {
    return $this->deviceToken;
  }
}
