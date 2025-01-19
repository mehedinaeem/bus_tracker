from django.http import JsonResponse
from django.views.decorators.csrf import csrf_exempt
import json

@csrf_exempt
def receive_data(request):
    if request.method == 'POST':
        data = json.loads(request.body)
        # Process the data as needed
        return JsonResponse({'status': 'success', 'data': data})
    return JsonResponse({'status': 'failure', 'message': 'Invalid request'}, status=400)
