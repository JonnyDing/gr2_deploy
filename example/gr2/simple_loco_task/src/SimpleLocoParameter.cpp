#include "SimpleLocoParameter.hpp" 

void SimpleLocoParameter::load(const std::string& filename) {
    std::cout<<"Loading Parameter from "<<filename<<"SimpleLocoTask/config_gr2_locomotion.yaml"<<std::endl;
    base_config_file_path = filename;
    config_file_path = base_config_file_path + "SimpleLocoTask/config_gr2_mix.yaml";
    YAML::Node config = YAML::LoadFile(config_file_path);

    loadSimpleLocoTaskConfig(config);
    loadRlPolicyConfig(config);
    loadGaitConfig(config);
}

void SimpleLocoParameter::loadSimpleLocoTaskConfig(const YAML::Node& config) {
    try {
        dt = config["SimpleLocoRLTask_Config"]["dt"].as<double>();
        control_freq = config["SimpleLocoRLTask_Config"]["control_freq"].as<double>();
        cycle_time = confif["SimpleLocoRLTask_Config"]["cycle_time"].as<double>();
        robot_joint_num = config["SimpleLocoRLTask_Config"]["robot_joint_num"].as<int>();
        control_joint_num = config["SimpleLocoRLTask_Config"]["control_joint_num"].as<int>();
        
        kp_joint_space.setZero(robot_joint_num);
        kd_joint_space.setZero(robot_joint_num);
        default_pos.setZero(robot_joint_num);

        int index = 0;
        for (const auto& vec : config["SimpleLocoRLTask_Config"]["kp_joint_space"]) {
            for (const auto& value : vec) {
                kp_joint_space(index++) = value.as<double>();
            }
        }

        index = 0;
        for (const auto& vec : config["SimpleLocoRLTask_Config"]["kd_joint_space"]) {
            for (const auto& value : vec) {
                kd_joint_space(index++) = value.as<double>();
            }
        }

        index = 0;
        for (const auto& vec : config["SimpleLocoRLTask_Config"]["default_pos"]) {
            for (const auto& value : vec) {
                default_pos(index++) = value.as<double>();
            }
        }

    } 
    catch (const std::exception& e) {
        std::cerr << "Failed to load simple loco task config " << ": " << e.what() << std::endl;
        exit(0);
    }
}

void SimpleLocoParameter::loadRlPolicyConfig(const YAML::Node& config) {
    try {
        std::string policy_name = config["SimpleLocoRLPolicy_Config"]["policy_path"].as<std::string>();
        policy_path = base_config_file_path + "SimpleLocoTask/" + policy_name;
        std::cout<<"policy_path: "<<policy_path<<std::endl;

        obs_scales_lin_vel = config["SimpleLocoRLPolicy_Config"]["obs_scales_lin_vel"].as<double>();
        obs_scales_ang_vel = config["SimpleLocoRLPolicy_Config"]["obs_scales_ang_vel"].as<double>();
        obs_scale_gravity = config["SimpleLocoRLPolicy_Config"]["obs_scale_gravity"].as<double>();
        obs_scale_joint_pos = config["SimpleLocoRLPolicy_Config"]["obs_scale_joint_pos"].as<double>();
        obs_scale_joint_vel = config["SimpleLocoRLPolicy_Config"]["obs_scale_joint_vel"].as<double>();
        obs_scale_height_measurements = config["SimpleLocoRLPolicy_Config"]["obs_scale_height_measurements"].as<double>();
        obs_scale_action = config["SimpleLocoRLPolicy_Config"]["obs_scale_action"].as<double>();

        auto act_scale_action_vec = config["SimpleLocoRLPolicy_Config"]["act_scale_action"].as<std::vector<double>>();
        act_scale_action = Eigen::VectorXd::Map(act_scale_action_vec.data(), act_scale_action_vec.size());

        num_actor_obs = config["SimpleLocoRLPolicy_Config"]["num_actor_obs"].as<int>();
        num_actor_hist = config["SimpleLocoRLPolicy_Config"]["num_actor_hist"].as<int>();

        command_filter_cf = config["SimpleLocoRLPolicy_Config"]["command_filter_cf"].as<double>();
        command_safety_ratio = config["SimpleLocoRLPolicy_Config"]["command_safety_ratio"].as<double>();

        auto vel_x_vec = config["SimpleLocoRLPolicy_Config"]["command_vel_x_range"].as<std::vector<double>>();
        command_vel_x_range = Eigen::Vector2d::Map(vel_x_vec.data(), vel_x_vec.size());
        
        auto vel_y_vec = config["SimpleLocoRLPolicy_Config"]["command_vel_y_range"].as<std::vector<double>>();
        command_vel_y_range = Eigen::Vector2d::Map(vel_y_vec.data(), vel_y_vec.size());
        
        auto vel_yaw_vec = config["SimpleLocoRLPolicy_Config"]["command_vel_yaw_range"].as<std::vector<double>>();
        command_vel_yaw_range = Eigen::Vector2d::Map(vel_yaw_vec.data(), vel_yaw_vec.size());

        auto actor_output_max_vec = config["SimpleLocoRLPolicy_Config"]["actor_output_max"].as<std::vector<double>>();
        actor_output_max = Eigen::VectorXd::Map(actor_output_max_vec.data(), actor_output_max_vec.size());

        auto actor_output_min_vec = config["SimpleLocoRLPolicy_Config"]["actor_output_min"].as<std::vector<double>>();
        actor_output_min = Eigen::VectorXd::Map(actor_output_min_vec.data(), actor_output_min_vec.size());

        auto actor_output_clip_margin_max_vec = config["SimpleLocoRLPolicy_Config"]["actor_output_clip_margin_max"].as<std::vector<double>>();
        actor_output_clip_margin_max = Eigen::VectorXd::Map(actor_output_clip_margin_max_vec.data(), actor_output_clip_margin_max_vec.size());

        auto actor_output_clip_margin_min_vec = config["SimpleLocoRLPolicy_Config"]["actor_output_clip_margin_min"].as<std::vector<double>>();
        actor_output_clip_margin_min = Eigen::VectorXd::Map(actor_output_clip_margin_min_vec.data(), actor_output_clip_margin_min_vec.size());

        std::cout<<"actor_output_max: "<<actor_output_max.transpose()<<std::endl;
        std::cout<<"actor_output_min: "<<actor_output_min.transpose()<<std::endl;
        std::cout<<"actor_output_clip_margin_max: "<<actor_output_clip_margin_max.transpose()<<std::endl;
        std::cout<<"actor_output_clip_margin_min: "<<actor_output_clip_margin_min.transpose()<<std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Failed to load rl policy config " << ": " << e.what() << std::endl;
        exit(0);
    }
}

