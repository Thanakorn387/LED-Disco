from django.urls import path
from . import views

urlpatterns = [
    path('', views.index, name='index'),
    path('add/', views.add_movie, name='add_movie'),
    path('edit/<int:id>/', views.edit_movie, name='edit_movie'),
    path('delete/<int:id>/', views.delete_movie, name='delete_movie'),
]
