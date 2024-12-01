from django.contrib import admin
from .models import MovieOrAnime

@admin.register(MovieOrAnime)
class MovieOrAnimeAdmin(admin.ModelAdmin):
    list_display = ('favorite_order', 'title_th', 'title_en', 'seasons', 'viewing_platform')
