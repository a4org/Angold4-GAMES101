#include "Triangle.hpp"
#include "rasterizer.hpp"
#include <eigen3/Eigen/Eigen>
#include <eigen3/Eigen/src/Core/util/Constants.h>
#include <iostream>
#include <opencv2/opencv.hpp>

constexpr double MY_PI = 3.1415926;

Eigen::Matrix4f get_view_matrix(Eigen::Vector3f eye_pos)
{
    Eigen::Matrix4f view = Eigen::Matrix4f::Identity();

    // Parallel to the coordinate axis (only need to do translation)
    Eigen::Matrix4f translate;
    translate << 1, 0, 0, -eye_pos[0], 0, 1, 0, -eye_pos[1], 0, 0, 1,
        -eye_pos[2], 0, 0, 0, 1;

    view = translate * view;

    return view;
}

Eigen::Matrix4f get_model_matrix(float rotation_angle)
{
    Eigen::Matrix4f model = Eigen::Matrix4f::Identity();
    
    Eigen::Matrix4f translate;
    double a = rotation_angle/180 * acos(-1);
    translate << cos(a),-sin(a), 0, 0,
              sin(a), cos(a), 0, 0,
              0, 0, 1, 0,
              0, 0, 0, 1;

    model = translate * model;
    return model;
}

Eigen::Matrix4f get_projection_matrix(float eye_fov, float aspect_ratio,
                                      float zNear, float zFar)
{
    // Students will implement this function

    Eigen::Matrix4f projection = Eigen::Matrix4f::Identity();
    Eigen::Matrix4f P2O = Eigen::Matrix4f::Identity(); 
    // Perspective Matrix to Orthographic Matrix
    P2O << zNear, 0, 0, 0,
         0, zNear, 0, 0,
         0, 0, zNear+zFar,(-1)*zFar*zNear,
         0, 0, 1, 0;
    float halfEyeAngelRadian = eye_fov/2.0/180.0*MY_PI;
    float t = zNear*std::tan(halfEyeAngelRadian); // Get half Y
    float r=t*aspect_ratio; // Get half X
    float l=(-1)*r;
    float b=(-1)*t;
    Eigen::Matrix4f ortho1=Eigen::Matrix4f::Identity(); 
    // orthographic transformation
    ortho1<<2/(r-l),0,0,0, 
        0,2/(t-b),0,0,
        0,0,2/(zNear-zFar),0,
        0,0,0,1;
    Eigen::Matrix4f ortho2 = Eigen::Matrix4f::Identity();
    ortho2<<1,0,0,(-1)*(r+l)/2,
        0,1,0,(-1)*(t+b)/2,
        0,0,1,(-1)*(zNear+zFar)/2,
        0,0,0,1;
    Eigen::Matrix4f Matrix_ortho = ortho1 * ortho2;
    // M_persp = M_ortho * M_persp->ortho
    projection = Matrix_ortho * P2O;
    return projection;

}

int main(int argc, const char** argv)
{
    float angle = 0;
    bool command_line = false;
    std::string filename = "output.png";

    if (argc >= 3) {
        command_line = true;
        angle = std::stof(argv[2]); // -r by default
        if (argc == 4) {
            filename = std::string(argv[3]);
        }
        else
            return 0;
    }

    rst::rasterizer r(700, 700); // initialized (namespace rst is the namespace of rasterizer)

    Eigen::Vector3f eye_pos = {0, 0, 5};

    // The coordinates of the three vertices of the triangle
    std::vector<Eigen::Vector3f> pos{{2, 0, -2}, {0, 2, -2}, {-2, 0, -2}};

    // camera position
    std::vector<Eigen::Vector3i> ind{{0, 1, 2}};

    auto pos_id = r.load_positions(pos);
    auto ind_id = r.load_indices(ind);

    int key = 0;
    int frame_count = 0;

    if (command_line) {
        r.clear(rst::Buffers::Color | rst::Buffers::Depth);

        r.set_model(get_model_matrix(angle));
        r.set_view(get_view_matrix(eye_pos));
        r.set_projection(get_projection_matrix(45, 1, 0.1, 50));

        r.draw(pos_id, ind_id, rst::Primitive::Triangle);
        cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());
        image.convertTo(image, CV_8UC3, 1.0f);

        cv::imwrite(filename, image);

        return 0;
    }

    while (key != 27) {
        r.clear(rst::Buffers::Color | rst::Buffers::Depth);

        // mvp
        r.set_model(get_model_matrix(angle));
        r.set_view(get_view_matrix(eye_pos));
        r.set_projection(get_projection_matrix(45, 1, 0.1, 50));

        // using Bresenham's drawing algorithm to draw the trangle
        r.draw(pos_id, ind_id, rst::Primitive::Triangle);

        // opencv
        // r.frame_buffer().data() is the beginning addr of the frame buffer
        cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());
        image.convertTo(image, CV_8UC3, 1.0f);
        cv::imshow("image", image);
        key = cv::waitKey(10);

        std::cout << "frame count: " << frame_count++ << '\n';

        if (key == 'a') {
            angle += 10;
        }
        else if (key == 'd') {
            angle -= 10;
        }
    }

    return 0;
}
