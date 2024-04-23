extends TileMap


var adjacency_matrix = []


func _ready():
	
	var tilemap_size = get_used_rect().end - get_used_rect().position
	var map_rect = Rect2i(Vector2i.ZERO, tilemap_size)
	
	var tile_size = get_tileset().tile_size
	
	for j in range(tilemap_size.y):
		var row = []
		for i in range(tilemap_size.x):
			var coords = Vector2i(i, j)
			var tile_data = get_cell_tile_data(1, coords)
			if tile_data and tile_data.get_custom_data('type') == 'wall':
				row.append(1)
			else:
				row.append(0)
		adjacency_matrix.append(row)

	for row in adjacency_matrix:
		print(row)
		
func get_matrix():
	return adjacency_matrix
	
func _process(delta):
	pass
