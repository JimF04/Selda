extends CharacterBody2D

var current_Enemy_Coords

var tile_size = Vector2(16, 16)

var startPosition
var endPosition

@export var speed = 20
@export var limit = 0.5


func _ready():
	# Obtener la matriz de adyacencia del TileMap
	var tilemap = get_node("/root/World/TileMap")
	var adjacency_matrix = tilemap.get_matrix()
	get_Enemy_Coord()
	
	startPosition = position
	endPosition = startPosition + Vector2(1, 3*16)
	
func changeDirection():
	var tempEnd = endPosition
	endPosition = startPosition
	startPosition = tempEnd

func updateVelocity():
	var moveDirection = (endPosition - position)
	if moveDirection.length() < limit:
		changeDirection()
	velocity = moveDirection.normalized()*speed
	
func get_Player_Coords():
		# Obtener una referencia al TileMap
	var player = get_node("/root/World/TileMap/Player")
	# Obtener la matriz de adyacencia del TileMap
	var playerCoords = player.get_Player_Coords()
	
	return playerCoords
	
	
func get_Enemy_Coord():
	# Obtener la posición actual del jugador
	var enemy_position = global_position
	#print(player_position)
	# Convertir la posición del jugador a coordenadas de la matriz
	var enemy_cell_x = int(enemy_position.x / tile_size.x)
	var enemy_cell_y = int(enemy_position.y / tile_size.y)
	
	current_Enemy_Coords = Vector2(enemy_cell_x, enemy_cell_y)
	#print("Posicion actual del enemigo en la matriz: ", current_Enemy_Coords)
	return current_Enemy_Coords

#==========================================Peticiones==================================================

func _on_request_completed(result, response_code, headers, body):
	if response_code == 200:
		#print("Response Body:", body)
		var response_data = JSON.parse_string(body.get_string_from_utf8())
		print(response_data["status"])
		
	else:
		print("Error:", response_code, body)

func send_Player_And_Enemy_Coords():
	var player_coords = get_Player_Coords()
	var enemy_coords = get_Enemy_Coord()
	
	var tilemap = get_node("/root/World/TileMap")
	var adjacency_matrix = tilemap.get_matrix()
	
	# Configurar y enviar la solicitud HTTP al servidor con las coordenadas del jugador y del enemigo
	var url = "http://localhost:18080/send_coordinates"
	var headers = ["Content-Type: application/json"]
	var json_data = {"player_coords": player_coords, "enemy_coords": enemy_coords, "map": adjacency_matrix}
	$HTTPRequest.request_completed.connect(_on_request_completed)
	$HTTPRequest.request(url, headers, HTTPClient.METHOD_POST, JSON.stringify(json_data))



func _physics_process(delta):
	send_Player_And_Enemy_Coords()
	updateVelocity()
	move_and_slide()

