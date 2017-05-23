<?php

/**
 * @file
 * Defines additional tokens for order email.
 */

/**
 * Implements hook_token_info_alter().
 */
function commerce_email_token_info_alter(&$data) {
  $data['tokens']['commerce-order']['commerce-email-order-items'] = array(
    'name' => t('Order Items'),
    'description' => t('A table containing order items.'),
  );
   $data['tokens']['commerce-order']['commerce-email-payment-information'] = array(
    'name' => t('Payment Info'),
    'description' => t('A table containing Payment Info.'),
  );
  $data['tokens']['commerce-order']['commerce-email-order-information'] = array(
    'name' => t('Order Info'),
    'description' => t('A table containing Order Info.'),
  );  
}

/**
 * Implements hook_tokens().
 */
function commerce_email_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $url_options = array('absolute' => TRUE);

  if (isset($options['language'])) {
    $url_options['language'] = $options['language'];
    $language_code = $options['language']->language;
  }
  else {
    $language_code = NULL;
  }

  $sanitize = !empty($options['sanitize']);

  $replacements = array();

  if ($type == 'commerce-order' && !empty($data['commerce-order'])) {
    $order = $data['commerce-order'];

    foreach ($tokens as $name => $original) {
		if($name=='commerce-email-order-items'){
          $order_items = commerce_email_order_items($order);
          $replacements[$original] = $order_items;
		}
		if($name=='commerce-email-payment-information'){
          $order_items_payment = commerce_email_payment_information($order);
          $replacements[$original] = $order_items_payment;
		}
		if($name=='commerce-email-order-information'){
          $order_items_info = commerce_email_order_information($order);
          $replacements[$original] = $order_items_info;
		}
    }
  }
  return $replacements;
}
