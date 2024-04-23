extends CharacterBody2D

var current_Enemy_Coords

func _ready():
	# Obtener una referencia al TileMap
	var tilemap = get_node("/root/World/TileMap")
	# Obtener la matriz de adyacencia del TileMap
	var adjacency_matrix = tilemap.get_matrix()
	
func get_Enemy_Coord():
	# Obtener la posición actual del jugador
	var enemy_position = global_position
	#print(player_position)
	# Convertir la posición del jugador a coordenadas de la matriz
	var tilemap = get_node("/root/World/TileMap")
	var tile_size = Vector2(16, 16)
	var enemy_cell_x = int(enemy_position.x / tile_size.x)
	var enemy_cell_y = int(enemy_position.y / tile_size.y)
	
	current_Enemy_Coords = Vector2(enemy_cell_x, enemy_cell_y)
	#print("Posicion actual del enemigo en la matriz: ", current_Enemy_Coords)
	return current_Enemy_Coords

func get_Player_Coords():
		# Obtener una referencia al TileMap
	var player = get_node("/root/World/TileMap/Player")
	# Obtener la matriz de adyacencia del TileMap
	var playerCoords = player.get_Player_Coords()
	var enemyCoords = get_Enemy_Coord()
	
	print("Player: ", playerCoords, " Enemy: ", enemyCoords)
	
func _physics_process(delta):
	get_Enemy_Coord()
