Apple Push Notification Sender
==============================

These PHP classes make sending push notifications a breeze.

Example Usage
-------------

Include both `AppAPNSender.class.inc` and `AppNotification.class.inc` into your PHP script.

    // notifications to send
    $notifications = array();
    $notifications[] = new AppNotification('devicetokenhere1', 'Your message text goes here.');
    $notifications[] = new AppNotification('devicetokenhere2', 'Your message text goes here.');
    $notifications[] = new AppNotification('devicetokenhere3', 'Your message text goes here.');

    $pemPath = certkeyfile.pem';
    $passphrase = '';
    $sandboxMode = FALSE;

    $apn = new AppAPNSender($pemPath, $passphrase, $sandboxMode);
    if (!$apn->openConnection()) {

      // send some messages
      foreach ($notifications as $note) {
        $apn->postNotification($note->getAPNPayload(), $note->getDeviceToken());
      }

      $apn->closeConnection();
    }

Copyright
---------

Copyright (c) 2013 Brightec Ltd.