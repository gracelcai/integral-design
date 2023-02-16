import 'package:flutter/material.dart';
import './location_search_screen.dart';
import './theme.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'The Flutter Way',
      theme: lightTheme(context),
      home: const SearchLocationScreen(),
    );
  }
}
