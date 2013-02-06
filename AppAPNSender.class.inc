<?php

/**
 * Basic Apple Push Notification sender
 *
 * @package default
 * @author Cameron Cooke
 **/
class AppAPNSender
{
  private $sandboxHost = 'gateway.sandbox.push.apple.com';
  private $productionHost = 'gateway.push.apple.com';

  private $isSandboxMode = FALSE;
  private $port  = 2195;
  private $pemPath;
  private $passphrase;

  private $streamContext;
  private $apns;


  /**
   * Constructor
   *
   * @param string $pemPath path to .pem file that holds the cet and private key
   * @param string $passphrase optional passphrase required to access the .pem file
   * @param bool $sandbox if TRUE will use Apple's sandboxed gateway. Default is FALSE.
   * @return void
   **/
  function __construct($pemPath, $passphrase = NULL, $sandbox = FALSE)
  {
    $this->pemPath = $pemPath;
    $this->passphrase = $passphrase;
    $this->isSandboxMode = $sandbox;
  }


  /**
   * Attempts to open a socket connection to an Apple APN server
   *
   * @return Returns FALSE is connection fails
   **/
  public function openConnection()
  {
    $this->streamContext = stream_context_create();
    stream_context_set_option($this->streamContext, 'ssl', 'local_cert', $this->pemPath);
    if (!empty($this->passphrase)) {
        stream_context_set_option($this->streamContext, 'ssl', 'passphrase', $this->passphrase);
    }

    if ($this->isSandboxMode) {
      $this->apns = stream_socket_client('ssl://' . $this->sandboxHost . ':' . $this->port, $error, $errorString, 2, STREAM_CLIENT_CONNECT, $this->streamContext);
    }
    else {
      $this->apns = stream_socket_client('ssl://' . $this->productionHost . ':' . $this->port, $error, $errorString, 2, STREAM_CLIENT_CONNECT, $this->streamContext);
    }

    if (!$this->apns) {
      return FALSE;
    }
  }


  /**
   * Closes a previously opened socket connection
   *
   * @return void
   **/
  public function closeConnection() {
    if (!$this->apns) {
      fclose($this->apns);
    }
  }


  /**
   * Attempts to send a new notification to Apple via an existing open
   * connection.
   *
   * @param string $payload APN payload JSON
   * @param string $deviceToken the device token to send to Apple used for matching up the message and user's device
   * @return Returns FALSE if connection is not open
   **/
  public function postNotification($payload, $deviceToken)
  {
    if (!$this->apns) {
      return NO;
    }

    $apnsMessage = chr(0) . chr(0) . chr(32) . pack('H*', str_replace(' ', '', $deviceToken)) . chr(0) . chr(strlen($payload)) . $payload;
    fwrite($this->apns, $apnsMessage);
  }
}
