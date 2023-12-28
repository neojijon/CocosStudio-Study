<GameFile>
  <PropertyGroup Name="MainScene" Type="Scene" ID="a2ee0952-26b5-49ae-8bf9-4f1d6279b798" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="40" Speed="1.0000" ActivedAnimationName="titleAni">
        <Timeline ActionTag="2050852185" Property="Position">
          <PointFrame FrameIndex="0" X="496.9974" Y="546.2776">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="20" X="496.9974" Y="546.2776">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="40" X="496.9974" Y="546.2776">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="2050852185" Property="Scale">
          <ScaleFrame FrameIndex="0" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="20" X="1.1000" Y="1.1000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="40" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="2050852185" Property="RotationSkew">
          <ScaleFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="20" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="40" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="-1342457979" Property="Position">
          <PointFrame FrameIndex="0" X="816.3298" Y="45.7483">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="40" X="847.5646" Y="45.7485">
            <EasingData Type="6" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="-1342457979" Property="Scale">
          <ScaleFrame FrameIndex="0" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="-1342457979" Property="RotationSkew">
          <ScaleFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="StartbtnAni" StartIndex="0" EndIndex="40">
          <RenderColor A="255" R="222" G="184" B="135" />
        </AnimationInfo>
        <AnimationInfo Name="titleAni" StartIndex="0" EndIndex="60">
          <RenderColor A="255" R="112" G="128" B="144" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Scene" ctype="GameNodeObjectData">
        <Size X="960.0000" Y="640.0000" />
        <Children>
          <AbstractNodeData Name="Image_1" ActionTag="1677859838" Tag="3" IconVisible="False" LeftMargin="2.6195" RightMargin="-2.6195" TopMargin="0.0518" BottomMargin="-0.0518" LeftEage="15" RightEage="15" TopEage="15" BottomEage="15" Scale9OriginX="15" Scale9OriginY="15" Scale9Width="930" Scale9Height="610" ctype="ImageViewObjectData">
            <Size X="960.0000" Y="640.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="482.6195" Y="319.9482" />
            <Scale ScaleX="1.0009" ScaleY="1.0044" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5027" Y="0.4999" />
            <PreSize X="1.0000" Y="1.0000" />
            <FileData Type="Normal" Path="bg/background.png" Plist="" />
          </AbstractNodeData>
          <AbstractNodeData Name="Image_2" ActionTag="2050852185" Tag="4" IconVisible="False" LeftMargin="201.4974" RightMargin="167.5026" TopMargin="32.7224" BottomMargin="485.2776" LeftEage="227" RightEage="227" TopEage="61" BottomEage="61" Scale9OriginX="227" Scale9OriginY="61" Scale9Width="137" Scale9Height="1" ctype="ImageViewObjectData">
            <Size X="591.0000" Y="122.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="496.9974" Y="546.2776" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5177" Y="0.8536" />
            <PreSize X="0.6156" Y="0.1906" />
            <FileData Type="Normal" Path="Title2.png" Plist="" />
          </AbstractNodeData>
          <AbstractNodeData Name="StartBtn" ActionTag="-1342457979" Tag="5" IconVisible="False" LeftMargin="736.3298" RightMargin="63.6702" TopMargin="561.2517" BottomMargin="12.7483" TouchEnable="True" FontSize="36" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="130" Scale9Height="44" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="160.0000" Y="66.0000" />
            <Children>
              <AbstractNodeData Name="Text_1" ActionTag="-1256464442" Tag="6" IconVisible="False" LeftMargin="15.2598" RightMargin="54.7402" TopMargin="12.6421" BottomMargin="17.3579" FontSize="32" LabelText="Start" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="90.0000" Y="36.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="60.2598" Y="35.3579" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="0" />
                <PrePosition X="0.3766" Y="0.5357" />
                <PreSize X="0.5625" Y="0.5455" />
                <FontResource Type="Normal" Path="Maplestory Bold.ttf" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="816.3298" Y="45.7483" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.8503" Y="0.0715" />
            <PreSize X="0.1667" Y="0.1031" />
            <FontResource Type="Normal" Path="Maplestory Bold.ttf" Plist="" />
            <TextColor A="255" R="65" G="65" B="70" />
            <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
            <PressedFileData Type="Default" Path="Default/Button_Press.png" Plist="" />
            <NormalFileData Type="Normal" Path="StartBtn.png" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>