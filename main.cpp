#include <iostream>
#include "shader_utils.h"
#include <GLFW/glfw3.h>
using std::string ;
int main() {
    if (glfwInit() != GL_TRUE) {
        fprintf(stderr, "Failed to initialize GLFW\n") ;
        return -1 ;
    }
    check_gl_errors("glfw init") ;
    // Create a rendering window with OpenGL 3.2 context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3) ;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2) ;
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE) ;
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE) ;
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE) ;

    int window_h = 600, window_w = 800 ;
    GLFWwindow* window = glfwCreateWindow(window_w, window_h, "OpenGL", NULL, NULL) ;
    glfwMakeContextCurrent(window) ;
    check_gl_errors("glfw window context") ;
    glewExperimental = GL_TRUE ;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n") ;
        return -1 ;
    }
    check_gl_errors("glew set up") ;

    //=============================================================
    string invalid_frag_src = "invalid_fragment_shader.glsl" ;
    string invalid_vtx_src = "invalid_vertex_shader.glsl" ;
    string frag_src = "valid_fragment_shader.glsl" ;
    string vtx_src = "valid_vertex_shader.glsl" ;

    std::cout << "\n\nTesting shader_utils" << std::endl ;

    std::cout << "\nInvalid shaders\n" << std::endl ;

    GLuint ifrag = compile_fragment_shader(invalid_frag_src) ;
    print_shader_comp_info(ifrag) ;
    std::cout << "---------------------------------\n" ;
    GLuint ivtx = compile_vertex_shader(invalid_vtx_src) ;
    print_shader_comp_info(ivtx) ;
    std::cout << "---------------------------------\n" ;

    std::cout << "Linking invalid shaders" << std::endl ;
    GLuint iprog = create_program(ivtx, ifrag) ;
    print_shader_link_info(iprog) ;
    std::cout << "\n\n=================================\n" ;

    std::cout << "Valid shaders" << std::endl ;

    GLuint frag = compile_fragment_shader(frag_src) ;
    print_shader_comp_info(frag) ;
    std::cout << "---------------------------------\n" ;
    GLuint vtx = compile_vertex_shader(vtx_src) ;
    print_shader_comp_info(vtx) ;
    std::cout << "---------------------------------\n" ;

    std::cout << "Linking" << std::endl ;

    GLuint prog = create_program(vtx, frag) ;
    print_shader_link_info(prog) ;

    std::cout << "Done" << std::endl ;
    return 0;
}