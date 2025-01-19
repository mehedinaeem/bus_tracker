from django.contrib import admin
from django.urls import path,include
from . import views

urlpatterns = [
    path('admin/', admin.site.urls),
    path('bus/',include("bus.urls")),
    path('gsm/',include("gsm.urls")),
    path('',views.home,name='home'),

]
