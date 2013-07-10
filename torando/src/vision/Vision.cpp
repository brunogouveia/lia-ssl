/*
 * Vision.cpp
 *
 *  Created on: Apr 11, 2013
 *      Author: bruno
 */

#include "Vision.h"

RobotList Vision::robots;
RobotList Vision::opponents;

FieldInfo Vision::field;
BallInfo Vision::ball;
TargetFixed Vision::opponentGoal(3090.0, 0.0);
TargetFixed Vision::goal(-3090.0, 0.0);

Vision::Vision() {

}

Vision::~Vision() {
}

void Vision::startModule() {
	getInstance().start();
}

void Vision::stopModule() {
	getInstance().stop();
}

void Vision::changeInterval(int milSeconds) {
	getInstance().setInterval(milSeconds);
}

void Vision::onPreExecute() {
	client.open(true);
}

void Vision::doInBackground() {

	if (client.receive(packet)) {

		if (packet.has_detection()) {
			SSL_DetectionFrame detection = packet.detection();

			//Display the contents of the robot detection results:
			int balls_n = detection.balls_size();
			int robots_blue_n = detection.robots_blue_size();
			int robots_yellow_n = detection.robots_yellow_size();

			//Ball info:
			int correctBallId = -1;
			SSL_DetectionBall current;
			SSL_DetectionBall correctBall;
			int ballConfidence = 0.0;
			static int ballMiss = 0;
			for (int i = 0; i < balls_n; i++) {
				current = detection.balls(i);
				if (current.confidence() > ballConfidence) {
					ballConfidence = detection.balls(i).confidence();
					correctBallId = i;
					correctBall = current;
				}
			}

			if (correctBallId != -1) {
				Vision::ball.updateBall(correctBall);
				Vision::ball._confidence = correctBall.confidence();
				ballMiss = 0;
			} else {
				ballMiss++;
			}
			Vision::ball._onField = !(ballMiss > 10);

			//Blue robot info:
			RobotList & blueTeam = (BLUE_TEAM) ? Vision::robots : Vision::opponents;

			for (int i = 0; i < robots_blue_n; i++) {
				blueTeam.updateRobot(detection.robots_blue(i));
			}
			for (int i = 0; i < 10; i++) {
				blueTeam.robots[i]._onField = !(++(blueTeam.robotsMisses[i]) > 10);
			}

			//Yellow robot info:
			RobotList & yellowTeam = (BLUE_TEAM) ? Vision::opponents : Vision::robots;

			for (int i = 0; i < robots_yellow_n; i++) {
				yellowTeam.updateRobot(detection.robots_yellow(i));
			}
			for (int i = 0; i < 10; i++) {
				yellowTeam.robots[i]._onField = !(++(yellowTeam.robotsMisses[i]) > 10);
			}

		}

		//see if packet contains geometry data:
		if (packet.has_geometry()) {
			const SSL_GeometryData & geom = packet.geometry();
			//printf("-[Geometry Data]-------\n");

			const SSL_GeometryFieldSize & field = geom.field();
			/*printf("Field Dimensions:\n");
			 printf("  -line_width=%d (mm)\n", field.line_width());
			 printf("  -field_length=%d (mm)\n", field.field_length());
			 printf("  -field_width=%d (mm)\n", field.field_width());
			 printf("  -boundary_width=%d (mm)\n", field.boundary_width());
			 printf("  -referee_width=%d (mm)\n", field.referee_width());
			 printf("  -goal_width=%d (mm)\n", field.goal_width());
			 printf("  -goal_depth=%d (mm)\n", field.goal_depth());
			 printf("  -goal_wall_width=%d (mm)\n", field.goal_wall_width());
			 printf("  -center_circle_radius=%d (mm)\n", field.center_circle_radius());
			 printf("  -defense_radius=%d (mm)\n", field.defense_radius());
			 printf("  -defense_stretch=%d (mm)\n", field.defense_stretch());
			 printf("  -free_kick_from_defense_dist=%d (mm)\n", field.free_kick_from_defense_dist());
			 printf("  -penalty_spot_from_field_line_dist=%d (mm)\n", field.penalty_spot_from_field_line_dist());
			 printf("  -penalty_line_from_spot_dist=%d (mm)\n", field.penalty_line_from_spot_dist());*/

			int calib_n = geom.calib_size();
			for (int i = 0; i < calib_n; i++) {
				const SSL_GeometryCameraCalibration & calib = geom.calib(i);
				/*printf("Camera Geometry for Camera ID %d:\n", calib.camera_id());
				 printf("  -focal_length=%.2f\n", calib.focal_length());
				 printf("  -principal_point_x=%.2f\n", calib.principal_point_x());
				 printf("  -principal_point_y=%.2f\n", calib.principal_point_y());
				 printf("  -distortion=%.2f\n", calib.distortion());
				 printf("  -q0=%.2f\n", calib.q0());
				 printf("  -q1=%.2f\n", calib.q1());
				 printf("  -q2=%.2f\n", calib.q2());
				 printf("  -q3=%.2f\n", calib.q3());
				 printf("  -tx=%.2f\n", calib.tx());
				 printf("  -ty=%.2f\n", calib.ty());
				 printf("  -tz=%.2f\n", calib.tz());*/

				if (calib.has_derived_camera_world_tx() && calib.has_derived_camera_world_ty() && calib.has_derived_camera_world_tz()) {
					/*printf("  -derived_camera_world_tx=%.f\n", calib.derived_camera_world_tx());
					 printf("  -derived_camera_world_ty=%.f\n", calib.derived_camera_world_ty());
					 printf("  -derived_camera_world_tz=%.f\n", calib.derived_camera_world_tz());*/
				}

			}
		}
	}

}

void Vision::onPosExecute() {
	client.close();
}

bool Vision::isFree(Target self, Target position, double tolerance, bool avoidBall) {

	bool free = true;

	int numRobots = Vision::robots.size();
	for (int i = 0; i < numRobots; i++)
		if (position.distanceTo(Vision::robots[i]) < tolerance && self.distanceTo(Vision::robots[i]) > ROBOT_RADIUS)
			free = false;

	numRobots = Vision::opponents.size();
	for (int i = 0; i < numRobots; i++)
		if (position.distanceTo(Vision::opponents[i]) < tolerance && self.distanceTo(Vision::opponents[i]) > ROBOT_RADIUS)
			free = false;

	if (position.distanceTo(Vision::ball) < tolerance && avoidBall)
		free = false;

	return free;

}
