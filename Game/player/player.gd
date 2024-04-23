extends CharacterBody2D

@export var speed: int = 100
@onready var animations = $AnimationPlayer

var current_Player_Coords

func handleInput():
	var moveDirection = Input.get_vector("ui_left", "ui_right", "ui_up", "ui_down")
	velocity = moveDirection*speed

func updateAnimation():
	if velocity.length() == 0:
		if animations.is_playing():
			animations.stop()
	else:
		var direction = "Down"
		if velocity.x < 0: direction = "Left"
		elif velocity.x > 0: direction = "Right"
		elif velocity.y < 0: direction = "Up"
	
		animations.play("walk" + direction)
		
func _ready():
	# Obtener una referencia al TileMap
	var tilemap = get_node("/root/World/TileMap")
	# Obtener la matriz de adyacencia del TileMap
	var adjacency_matrix = tilemap.get_matrix()
	
func get_Player_Coords():
	# Obtener la posición actual del jugador
	var player_position = global_position
	#print(player_position)
	# Convertir la posición del jugador a coordenadas de la matriz
	var tilemap = get_node("/root/World/TileMap")
	var tile_size = Vector2(16, 16)
	var player_cell_x = int(player_position.x / tile_size.x)
	var player_cell_y = int(player_position.y / tile_size.y)
	
	current_Player_Coords = Vector2(player_cell_x, player_cell_y)
	#print("Posicion actual del jugador en la matriz: ", current_Player_Coords)
	return current_Player_Coords

func _physics_process(delta):
	handleInput()
	move_and_slide()
	updateAnimation()
	get_Player_Coords()

