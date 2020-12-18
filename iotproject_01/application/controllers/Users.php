<?php
class Users extends CI_Controller {

        public function __construct()
        {
            parent::__construct();
            $this->load->model('user_model');
            $this->load->helper('url_helper', 'form');
            $this->load->database();
        }

        public function view($username = NULL)
        {
            $data['user_item'] = $this->user_model->get_users($slug);
        }

        public function index()
        {
            $data['username'] = $this->user_model->get_users();
            $data['password'] = 'News archive';
            $this->load->controllers->Pages->view($page = 'home');
            $data['title'] = ucfirst(testi);
            $this->load->view('templates/header', $data);
            $this->load->view('pages/user', $data);
            $this->load->view('templates/footer');
        }

        public function login_check()
        {
            $username = $this->input->post("username");
            $password = $this->input->post("password");

            echo $username;
            echo "<br>";
            echo $password;
        }

}