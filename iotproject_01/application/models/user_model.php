<?php
class user_model extends CI_Model{
	
	public function __construct()
        {
                $this->load->database();
        }

        public function get_users($username = FALSE)
        {
                if ($username === FALSE)
                {
                        $query = $this->db->get('users');
                        return $query->result_array();
                }

                $query = $this->db->get_where('users', array('username' => $username));
                return $query->row_array();
        }
}