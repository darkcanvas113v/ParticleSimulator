namespace game {
  void init_board(
    int numOfParticles,
    float temperature
  );
  void clear_board();

  void physics_loop(float dt);
  void render_loop();

  void print_to_command_line();
}