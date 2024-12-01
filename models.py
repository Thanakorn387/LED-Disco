from django.db import models

class MovieOrAnime(models.Model):
    favorite_order = models.PositiveIntegerField()  
    title_th = models.CharField(max_length=255)  
    title_en = models.CharField(max_length=255)  
    seasons = models.PositiveIntegerField()  
    viewing_platform = models.CharField(max_length=255)  

    def __str__(self):
        return f"{self.title_th} ({self.title_en})"
