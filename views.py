from django.shortcuts import render, redirect, get_object_or_404
from .forms import MovieOrAnimeForm
from .models import MovieOrAnime


def add_movie(request):
    if request.method == 'POST':
        form = MovieOrAnimeForm(request.POST)
        if form.is_valid():
            form.save()
            return redirect('index')  
    else:
        form = MovieOrAnimeForm()
    
    return render(request, 'movies/add_movie.html', {'form': form})


def index(request):
    movies = MovieOrAnime.objects.all().order_by('favorite_order')
    return render(request, 'movies/index.html', {'movies': movies})


def edit_movie(request, id):
    movie = get_object_or_404(MovieOrAnime, id=id)
    if request.method == 'POST':
        form = MovieOrAnimeForm(request.POST, instance=movie)
        if form.is_valid():
            form.save()
            return redirect('index')  
    else:
        form = MovieOrAnimeForm(instance=movie)
    
    return render(request, 'movies/edit_movie.html', {'form': form})


def delete_movie(request, id):
    movie = get_object_or_404(MovieOrAnime, id=id)
    if request.method == 'POST':
        movie.delete()
        return redirect('index')  
    
    return render(request, 'movies/confirm_delete.html', {'movie': movie})
