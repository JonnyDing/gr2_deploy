/**
 * @file SimpleLocoParameter.hpp
 * @brief Header file for SimpleLocoParameter in robot controllers.
 *
 * @details 
 *
 * @author renminwansui
 * @date April 30, 2025
 * @version v1.0
 * @bug No known bugs
 *
 * @copyright Copyright (c) 2025, shanghai fourier intelligence
 */

#pragma once

#include <memory>
#include <iostream>
#include <mutex>
#include <Eigen/Dense>
#include "LoadFromYaml.hpp"

class SimpleLocoParameter : public LoadFromYaml {

public:
    SimpleLocoParameter(std::string filename) {
        load(filename);
    }
    
public:
    std::string base_config_file_path;
    
    std::string config_file_path;
    double dt;
    double control_freq;

    int robot_joint_num;
    int control_joint_num;

    Eigen::VectorXd default_pos;

    Eigen::VectorXd kp_joint_space;
    Eigen::VectorXd kd_joint_space;

    // Policy parameters
    std::string policy_path;
    double obs_scales_lin_vel;
    double obs_scales_ang_vel;

    double obs_scale_gravity;
    double obs_scale_joint_pos;
    double obs_scale_joint_vel;
    double obs_scale_height_measurements;

    double obs_scale_action;
    Eigen::VectorXd act_scale_action;

    int num_actor_obs;
    int num_actor_hist;

    Eigen::VectorXd actor_output_max;
    Eigen::VectorXd actor_output_min;
    Eigen::VectorXd actor_output_clip_margin_max;
    Eigen::VectorXd actor_output_clip_margin_min;

    double command_filter_cf;

    double command_safety_ratio;
    Eigen::Vector2d command_vel_x_range;
    Eigen::Vector2d command_vel_y_range;
    Eigen::Vector2d command_vel_yaw_range;

    double cycle_time;


 
 public:
    void load(const std::string& filename) override;
    void loadSimpleLocoTaskConfig(const YAML::Node& config);
    void loadRlPolicyConfig(const YAML::Node& config);

    Eigen::VectorXd yamlSequenceToVector(const YAML::Node& node) {
        Eigen::VectorXd vec(node.size());
        for (size_t i = 0; i < node.size(); ++i) {
            vec[i] = node[i].as<double>();
        }
        return vec;
    }
};