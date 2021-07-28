<?php

/**
 * The Auth0 basic configuration settings form callback.
 */
function auth0_basic_settings_form($form, &$form_state) {
  $form['auth0_domain'] = [
    '#type' => 'textfield',
    '#title' => t('Domain'),
    '#default_value' => variable_get('auth0_domain', ''),
    '#description' => t('Your Auth0 domain, you can see it in the auth0 dashboard.'),
    '#required' => TRUE,
  ];
  $form['auth0_client_id'] = [
    '#type' => 'textfield',
    '#title' => t('Client id'),
    '#default_value' => variable_get('auth0_client_id', ''),
    '#description' => t('Application id, copy from the auth0 dashboard.'),
    '#required' => TRUE,
  ];
  $form['auth0_client_secret'] = [
    '#type' => 'textfield',
    '#title' => t('Client secret'),
    '#default_value' => variable_get('auth0_client_secret', ''),
    '#description' => t('Application secret, copy from the auth0 dashboard.'),
    '#required' => TRUE,
  ];
  $form['auth0_secret_base64_encoded'] = [
    '#type' => 'checkbox',
    '#title' => t('Client Secret is Base64 Encoded'),
    '#default_value' => variable_get('auth0_secret_base64_encoded', FALSE),
    '#description' => t('This is stated below the client secret in your Auth0 Dashboard for the client.  If your client was created after September 2016, this should be false.'),
  ];
  $form['auth0_jwt_signature_alg'] = [
    '#type' => 'select',
    '#title' => t('JWT Signature Algorithm'),
    '#options' => [
      'HS256' => t('HS256'),
      'RS256' => t('RS256'),
    ],
    '#default_value' => variable_get('auth0_jwt_signature_alg', 'HS256'),
    '#description' => t('Your JWT Signing Algorithm for the ID token.  RS256 is recommended, but must be set in the advanced settings under oauth for this client.'),
    '#required' => TRUE,
  ];

  return system_settings_form($form);
}


/**
 * The Auth0 advanced configuration settings form callback.
 */
function auth0_advanced_settings_form($form, &$form_state) {
  $form['auth0_replace_forms'] = [
    '#type' => 'checkbox',
    '#title' => t('Replace default Drupal login, registration, and password reset forms'),
    '#default_value' => variable_get('auth0_replace_forms', TRUE),
    '#description' => t('Uncheck this box to disable replacement of the default Drupal login, registration, and password reset forms with the Auth0 Lock login widget. This allows maintaining the option to login with a Drupal username and password.'),
  ];

  // Text field for the e-mail subject.
  $form['auth0_form_title'] = [
    '#type' => 'textfield',
    '#title' => t('Form title'),
    '#default_value' => variable_get('auth0_form_title', 'Sign In'),
    '#description' => t('This is the title for the login widget.'),
  ];

  $form['auth0_allow_signup'] = [
    '#type' => 'checkbox',
    '#title' => t('Allow user signup'),
    '#default_value' => variable_get('auth0_allow_signup', TRUE),
    '#description' => t('If you have database connection you can allow users to signup using the Auth0 widget.'),
  ];


  $form['auth0_widget_cdn'] = [
    '#type' => 'textfield',
    '#title' => t('Widget CDN'),
    '#default_value' => variable_get('auth0_widget_cdn', AUTH0_WIDGET_CDN),
    '#description' => t('Point this to the latest widget available in the CDN.'),
  ];

  $form['auth0_requires_email'] = [
    '#type' => 'checkbox',
    '#title' => t('Require an e-mail account'),
    '#default_value' => variable_get('auth0_requires_email', TRUE),
    '#description' => t('Require the user to have an e-mail address to login.'),
  ];

  $form['auth0_join_user_by_mail_enabled'] = [
    '#type' => 'checkbox',
    '#title' => t('Link auth0 logins to drupal users by email address'),
    '#default_value' => variable_get('auth0_join_user_by_mail_enabled', FALSE),
    '#description' => t('If enabled, when a user logs into Drupal for the first time, the system will use the email 
address of the Auth0 user to search for a drupal user with the same email address and setup a link to that 
Drupal user account.
<br/>If not enabled, then a new Drupal user will be created even if a Drupal user with the same email address already exists.
'),
  ];

  $form['auth0_sso'] = [
    '#type' => 'checkbox',
    '#title' => t('SSO enabled'),
    '#default_value' => variable_get('auth0_sso', FALSE),
    '#description' => t('Enable Auth0 <a href="@url">Single Sign On</a> for this site.', ['@url' => 'https://auth0.com/docs/sso/single-sign-on']),
  ];

  $form['auth0_login_css'] = [
    '#type' => 'textarea',
    '#title' => t('Login widget CSS'),
    '#default_value' => variable_get('auth0_login_css', AUTH_LOGIN_CSS),
    '#description' => t('This CSS controls the widget look and feel.'),
  ];
  // Add option to have the logout url at the application level or account level
  $form['auth0_returnTo_app'] = [
    '#type' => 'checkbox',
    '#title' => t('Use returnTo URLs at the App Level'),
    '#default_value' => variable_get('auth0_returnTo_app', FALSE),
    '#description' => t('Check this box to use the <a href="@url">returnTo URLs</a> at the Account Level', ['@url' => 'https://auth0.com/docs/logout#redirecting-users-after-logout']),
  ];

  $form['auth0_lock_extra_settings'] = [
    '#type' => 'textarea',
    '#title' => t('Lock extra setting'),
    '#default_value' => variable_get('auth0_lock_extra_settings'),
    '#description' => t('This should be a valid JSON file. This entire object will be passed to the lock options parameter.'),
  ];

  $form['auth0_auto_register'] = [
    '#type' => 'checkbox',
    '#title' => t('Auto Register Auth0 users (ignore site registration settings)'),
    '#default_value' => variable_get('auth0_auto_register', FALSE),
    '#description' => t('Enable this option if you want new auth0 users to automatically be activated within Drupal regardless of the global site visitor registration settings (e.g. requiring admin approval).'),
  ];

  // Enhancement to support mapping claims to user attributes and to roles
  $form['auth0_claim_mapping'] = [
    '#type' => 'textarea',
    '#title' => t('Mapping of Claims to Profile Fields (one per line):'),
    '#cols' => 50,
    '#rows' => 5,
    '#default_value' => variable_get('auth0_claim_mapping'),
    '#description' => t('Enter claim mappings here in the format &lt;claim_name>|&lt;profile_field_name> (one per line), e.g:
<br/>
<br/>given_name|field_first_name
<br/>family_name|field_last_name
<br/>
<br/>NOTE: the following Drupal fields are handled automatically and will be ignored if specified above:
<br/>    uid, name, mail, init, is_new, status, pass
'),
  ];

  $form['auth0_claim_to_use_for_role'] = [
    '#type' => 'textfield',
    '#title' => t('Claim for Role Mapping:'),
    '#default_value' => variable_get('auth0_claim_to_use_for_role'),
    '#description' => t('Name of the claim to use to map to Drupal roles, e.g. roles.  If the claim contains a list of values, all values will be used in the mappings below.'),
  ];

  $form['auth0_role_mapping'] = [
    '#type' => 'textarea',
    '#title' => t('Mapping of Claim Role Values to Drupal Roles (one per line)'),
    '#default_value' => variable_get('auth0_role_mapping'),
    '#description' => t('Enter role mappings here in the format &lt;auth0 claim value>|&lt;drupal role name> (one per line), e.g.:
<br/>
<br/>admin|administrator
<br/>poweruser|power users
<br/>
<br/>NOTE: for any drupal role in the mapping, if a user is not mapped to the role, the role will be removed from their profile.  
Drupal roles not listed above will not be changed by this module.
'),
  ];

  return system_settings_form($form);
}
