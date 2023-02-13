import 'package:flutter/material.dart';
import 'package:flutter_svg/svg.dart';
import './models/autocomplate_prediction.dart';
import './models/place_auto_complate_response.dart';
import './network_utillity.dart';
import 'components/location_list_tile.dart';
import 'constants.dart';

class SearchLocationScreen extends StatefulWidget {
  const SearchLocationScreen({Key? key}) : super(key: key);

  @override
  State<SearchLocationScreen> createState() => _SearchLocationScreenState();
}

class _SearchLocationScreenState extends State<SearchLocationScreen> {
  List<AutocompletePrediction> placePredictions = [];

  void placeAutoComplete(String query) async {
    Uri uri = Uri.https(
        "maps.googleapis.com",
        'maps/api/place/autocomplete/json', //uneconder path
        {
          "input": query,
          "key": apiKey,
        });

    String? response = await NetworkUtility.fetchUrl(uri);

    if (response != null) {
      PlaceAutocompleteResponse result =
          PlaceAutocompleteResponse.parseAutocompleteResult(response);

      if (result.predictions != null) {
        setState(() {
          placePredictions = result.predictions!;
        });
      }
    }
  }

  @override
  Widget build(BuildContext context) {
    return Column(
      children: [
        Form(
          child: Padding(
            padding: const EdgeInsets.all(defaultPadding),
            child: TextFormField(
              onChanged: (value) {
                placeAutoComplete(value);
              },
              textInputAction: TextInputAction.search,
              decoration: InputDecoration(
                hintText: "Search your location",
                prefixIcon: Padding(
                  padding: const EdgeInsets.symmetric(vertical: 12),
                  child: SvgPicture.asset(
                    "assets/icons/location_pin.svg",
                    color: secondaryColor40LightTheme,
                  ),
                ),
              ),
            ),
          ),
        ),
        const Divider(
          height: 4,
          thickness: 4,
          color: secondaryColor5LightTheme,
        ),
        Padding(
          padding: const EdgeInsets.all(defaultPadding),
          child: ElevatedButton.icon(
            onPressed: () {},
            icon: SvgPicture.asset(
              "assets/icons/location.svg",
              height: 16,
            ),
            label: const Text("Use my Current Location"),
            style: ElevatedButton.styleFrom(
              backgroundColor: secondaryColor10LightTheme,
              foregroundColor: textColorLightTheme,
              elevation: 0,
              fixedSize: const Size(double.infinity, 40),
              shape: const RoundedRectangleBorder(
                borderRadius: BorderRadius.all(Radius.circular(10)),
              ),
            ),
          ),
        ),
        const Divider(
          height: 4,
          thickness: 4,
          color: secondaryColor5LightTheme,
        ),

        Expanded(
          child: ListView.builder(
              itemBuilder: (context, index) => LocationListTile(
                    press: () {},
                    location: placePredictions[index].description!,
                  )),
        )

        // LocationListTile(
        //   press: () {},
        //   location: "Banasree, Dhaka, Bangladesh",
        // ),
      ],
    );
  }
}
